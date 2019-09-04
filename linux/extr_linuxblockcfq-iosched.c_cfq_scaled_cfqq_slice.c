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
typedef  unsigned int u64 ;
struct cfq_queue {int /*<<< orphan*/  cfqg; } ;
struct cfq_data {unsigned int* cfq_slice; int cfq_slice_idle; scalar_t__ cfq_latency; } ;

/* Variables and functions */
 int /*<<< orphan*/  cfq_class_rt (struct cfq_queue*) ; 
 unsigned int cfq_group_get_avg_queues (struct cfq_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int cfq_group_slice (struct cfq_data*,int /*<<< orphan*/ ) ; 
 unsigned int cfq_prio_to_slice (struct cfq_data*,struct cfq_queue*) ; 
 unsigned int div64_u64 (unsigned int,unsigned int) ; 
 unsigned int max (unsigned int,unsigned int) ; 
 unsigned int min (unsigned int,unsigned int) ; 

__attribute__((used)) static inline u64
cfq_scaled_cfqq_slice(struct cfq_data *cfqd, struct cfq_queue *cfqq)
{
	u64 slice = cfq_prio_to_slice(cfqd, cfqq);
	if (cfqd->cfq_latency) {
		/*
		 * interested queues (we consider only the ones with the same
		 * priority class in the cfq group)
		 */
		unsigned iq = cfq_group_get_avg_queues(cfqd, cfqq->cfqg,
						cfq_class_rt(cfqq));
		u64 sync_slice = cfqd->cfq_slice[1];
		u64 expect_latency = sync_slice * iq;
		u64 group_slice = cfq_group_slice(cfqd, cfqq->cfqg);

		if (expect_latency > group_slice) {
			u64 base_low_slice = 2 * cfqd->cfq_slice_idle;
			u64 low_slice;

			/* scale low_slice according to IO priority
			 * and sync vs async */
			low_slice = div64_u64(base_low_slice*slice, sync_slice);
			low_slice = min(slice, low_slice);
			/* the adapted slice value is scaled to fit all iqs
			 * into the target latency */
			slice = div64_u64(slice*group_slice, expect_latency);
			slice = max(slice, low_slice);
		}
	}
	return slice;
}