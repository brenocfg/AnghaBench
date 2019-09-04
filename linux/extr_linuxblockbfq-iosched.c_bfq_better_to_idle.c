#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct bfq_queue {int wr_coeff; struct bfq_data* bfqd; } ;
struct bfq_data {scalar_t__ bfq_slice_idle; scalar_t__ wr_busy_queues; int /*<<< orphan*/  hw_tag; int /*<<< orphan*/  queue; scalar_t__ strict_guarantees; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFQQ_SEEKY (struct bfq_queue*) ; 
 scalar_t__ bfq_bfqq_IO_bound (struct bfq_queue*) ; 
 scalar_t__ bfq_bfqq_has_short_ttime (struct bfq_queue*) ; 
 int /*<<< orphan*/  bfq_bfqq_in_large_burst (struct bfq_queue*) ; 
 int /*<<< orphan*/  bfq_bfqq_sync (struct bfq_queue*) ; 
 scalar_t__ bfq_class_idle (struct bfq_queue*) ; 
 int /*<<< orphan*/  bfq_symmetric_scenario (struct bfq_data*) ; 
 int /*<<< orphan*/  blk_queue_nonrot (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool bfq_better_to_idle(struct bfq_queue *bfqq)
{
	struct bfq_data *bfqd = bfqq->bfqd;
	bool rot_without_queueing =
		!blk_queue_nonrot(bfqd->queue) && !bfqd->hw_tag,
		bfqq_sequential_and_IO_bound,
		idling_boosts_thr, idling_boosts_thr_without_issues,
		idling_needed_for_service_guarantees,
		asymmetric_scenario;

	if (bfqd->strict_guarantees)
		return true;

	/*
	 * Idling is performed only if slice_idle > 0. In addition, we
	 * do not idle if
	 * (a) bfqq is async
	 * (b) bfqq is in the idle io prio class: in this case we do
	 * not idle because we want to minimize the bandwidth that
	 * queues in this class can steal to higher-priority queues
	 */
	if (bfqd->bfq_slice_idle == 0 || !bfq_bfqq_sync(bfqq) ||
	    bfq_class_idle(bfqq))
		return false;

	bfqq_sequential_and_IO_bound = !BFQQ_SEEKY(bfqq) &&
		bfq_bfqq_IO_bound(bfqq) && bfq_bfqq_has_short_ttime(bfqq);

	/*
	 * The next variable takes into account the cases where idling
	 * boosts the throughput.
	 *
	 * The value of the variable is computed considering, first, that
	 * idling is virtually always beneficial for the throughput if:
	 * (a) the device is not NCQ-capable and rotational, or
	 * (b) regardless of the presence of NCQ, the device is rotational and
	 *     the request pattern for bfqq is I/O-bound and sequential, or
	 * (c) regardless of whether it is rotational, the device is
	 *     not NCQ-capable and the request pattern for bfqq is
	 *     I/O-bound and sequential.
	 *
	 * Secondly, and in contrast to the above item (b), idling an
	 * NCQ-capable flash-based device would not boost the
	 * throughput even with sequential I/O; rather it would lower
	 * the throughput in proportion to how fast the device
	 * is. Accordingly, the next variable is true if any of the
	 * above conditions (a), (b) or (c) is true, and, in
	 * particular, happens to be false if bfqd is an NCQ-capable
	 * flash-based device.
	 */
	idling_boosts_thr = rot_without_queueing ||
		((!blk_queue_nonrot(bfqd->queue) || !bfqd->hw_tag) &&
		 bfqq_sequential_and_IO_bound);

	/*
	 * The value of the next variable,
	 * idling_boosts_thr_without_issues, is equal to that of
	 * idling_boosts_thr, unless a special case holds. In this
	 * special case, described below, idling may cause problems to
	 * weight-raised queues.
	 *
	 * When the request pool is saturated (e.g., in the presence
	 * of write hogs), if the processes associated with
	 * non-weight-raised queues ask for requests at a lower rate,
	 * then processes associated with weight-raised queues have a
	 * higher probability to get a request from the pool
	 * immediately (or at least soon) when they need one. Thus
	 * they have a higher probability to actually get a fraction
	 * of the device throughput proportional to their high
	 * weight. This is especially true with NCQ-capable drives,
	 * which enqueue several requests in advance, and further
	 * reorder internally-queued requests.
	 *
	 * For this reason, we force to false the value of
	 * idling_boosts_thr_without_issues if there are weight-raised
	 * busy queues. In this case, and if bfqq is not weight-raised,
	 * this guarantees that the device is not idled for bfqq (if,
	 * instead, bfqq is weight-raised, then idling will be
	 * guaranteed by another variable, see below). Combined with
	 * the timestamping rules of BFQ (see [1] for details), this
	 * behavior causes bfqq, and hence any sync non-weight-raised
	 * queue, to get a lower number of requests served, and thus
	 * to ask for a lower number of requests from the request
	 * pool, before the busy weight-raised queues get served
	 * again. This often mitigates starvation problems in the
	 * presence of heavy write workloads and NCQ, thereby
	 * guaranteeing a higher application and system responsiveness
	 * in these hostile scenarios.
	 */
	idling_boosts_thr_without_issues = idling_boosts_thr &&
		bfqd->wr_busy_queues == 0;

	/*
	 * There is then a case where idling must be performed not
	 * for throughput concerns, but to preserve service
	 * guarantees.
	 *
	 * To introduce this case, we can note that allowing the drive
	 * to enqueue more than one request at a time, and hence
	 * delegating de facto final scheduling decisions to the
	 * drive's internal scheduler, entails loss of control on the
	 * actual request service order. In particular, the critical
	 * situation is when requests from different processes happen
	 * to be present, at the same time, in the internal queue(s)
	 * of the drive. In such a situation, the drive, by deciding
	 * the service order of the internally-queued requests, does
	 * determine also the actual throughput distribution among
	 * these processes. But the drive typically has no notion or
	 * concern about per-process throughput distribution, and
	 * makes its decisions only on a per-request basis. Therefore,
	 * the service distribution enforced by the drive's internal
	 * scheduler is likely to coincide with the desired
	 * device-throughput distribution only in a completely
	 * symmetric scenario where:
	 * (i)  each of these processes must get the same throughput as
	 *      the others;
	 * (ii) all these processes have the same I/O pattern
		(either sequential or random).
	 * In fact, in such a scenario, the drive will tend to treat
	 * the requests of each of these processes in about the same
	 * way as the requests of the others, and thus to provide
	 * each of these processes with about the same throughput
	 * (which is exactly the desired throughput distribution). In
	 * contrast, in any asymmetric scenario, device idling is
	 * certainly needed to guarantee that bfqq receives its
	 * assigned fraction of the device throughput (see [1] for
	 * details).
	 *
	 * We address this issue by controlling, actually, only the
	 * symmetry sub-condition (i), i.e., provided that
	 * sub-condition (i) holds, idling is not performed,
	 * regardless of whether sub-condition (ii) holds. In other
	 * words, only if sub-condition (i) holds, then idling is
	 * allowed, and the device tends to be prevented from queueing
	 * many requests, possibly of several processes. The reason
	 * for not controlling also sub-condition (ii) is that we
	 * exploit preemption to preserve guarantees in case of
	 * symmetric scenarios, even if (ii) does not hold, as
	 * explained in the next two paragraphs.
	 *
	 * Even if a queue, say Q, is expired when it remains idle, Q
	 * can still preempt the new in-service queue if the next
	 * request of Q arrives soon (see the comments on
	 * bfq_bfqq_update_budg_for_activation). If all queues and
	 * groups have the same weight, this form of preemption,
	 * combined with the hole-recovery heuristic described in the
	 * comments on function bfq_bfqq_update_budg_for_activation,
	 * are enough to preserve a correct bandwidth distribution in
	 * the mid term, even without idling. In fact, even if not
	 * idling allows the internal queues of the device to contain
	 * many requests, and thus to reorder requests, we can rather
	 * safely assume that the internal scheduler still preserves a
	 * minimum of mid-term fairness. The motivation for using
	 * preemption instead of idling is that, by not idling,
	 * service guarantees are preserved without minimally
	 * sacrificing throughput. In other words, both a high
	 * throughput and its desired distribution are obtained.
	 *
	 * More precisely, this preemption-based, idleless approach
	 * provides fairness in terms of IOPS, and not sectors per
	 * second. This can be seen with a simple example. Suppose
	 * that there are two queues with the same weight, but that
	 * the first queue receives requests of 8 sectors, while the
	 * second queue receives requests of 1024 sectors. In
	 * addition, suppose that each of the two queues contains at
	 * most one request at a time, which implies that each queue
	 * always remains idle after it is served. Finally, after
	 * remaining idle, each queue receives very quickly a new
	 * request. It follows that the two queues are served
	 * alternatively, preempting each other if needed. This
	 * implies that, although both queues have the same weight,
	 * the queue with large requests receives a service that is
	 * 1024/8 times as high as the service received by the other
	 * queue.
	 *
	 * On the other hand, device idling is performed, and thus
	 * pure sector-domain guarantees are provided, for the
	 * following queues, which are likely to need stronger
	 * throughput guarantees: weight-raised queues, and queues
	 * with a higher weight than other queues. When such queues
	 * are active, sub-condition (i) is false, which triggers
	 * device idling.
	 *
	 * According to the above considerations, the next variable is
	 * true (only) if sub-condition (i) holds. To compute the
	 * value of this variable, we not only use the return value of
	 * the function bfq_symmetric_scenario(), but also check
	 * whether bfqq is being weight-raised, because
	 * bfq_symmetric_scenario() does not take into account also
	 * weight-raised queues (see comments on
	 * bfq_weights_tree_add()).
	 *
	 * As a side note, it is worth considering that the above
	 * device-idling countermeasures may however fail in the
	 * following unlucky scenario: if idling is (correctly)
	 * disabled in a time period during which all symmetry
	 * sub-conditions hold, and hence the device is allowed to
	 * enqueue many requests, but at some later point in time some
	 * sub-condition stops to hold, then it may become impossible
	 * to let requests be served in the desired order until all
	 * the requests already queued in the device have been served.
	 */
	asymmetric_scenario = bfqq->wr_coeff > 1 ||
		!bfq_symmetric_scenario(bfqd);

	/*
	 * Finally, there is a case where maximizing throughput is the
	 * best choice even if it may cause unfairness toward
	 * bfqq. Such a case is when bfqq became active in a burst of
	 * queue activations. Queues that became active during a large
	 * burst benefit only from throughput, as discussed in the
	 * comments on bfq_handle_burst. Thus, if bfqq became active
	 * in a burst and not idling the device maximizes throughput,
	 * then the device must no be idled, because not idling the
	 * device provides bfqq and all other queues in the burst with
	 * maximum benefit. Combining this and the above case, we can
	 * now establish when idling is actually needed to preserve
	 * service guarantees.
	 */
	idling_needed_for_service_guarantees =
		asymmetric_scenario && !bfq_bfqq_in_large_burst(bfqq);

	/*
	 * We have now all the components we need to compute the
	 * return value of the function, which is true only if idling
	 * either boosts the throughput (without issues), or is
	 * necessary to preserve service guarantees.
	 */
	return idling_boosts_thr_without_issues ||
		idling_needed_for_service_guarantees;
}