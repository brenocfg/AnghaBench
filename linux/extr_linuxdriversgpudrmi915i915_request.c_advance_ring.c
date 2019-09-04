#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct intel_ring {unsigned int head; int /*<<< orphan*/  active_link; TYPE_1__* timeline; int /*<<< orphan*/  request_list; } ;
struct i915_request {unsigned int postfix; int /*<<< orphan*/  ring_link; int /*<<< orphan*/  tail; struct intel_ring* ring; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  GEM_TRACE (char*,int /*<<< orphan*/ ) ; 
 unsigned int READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_is_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_is_last (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void advance_ring(struct i915_request *request)
{
	struct intel_ring *ring = request->ring;
	unsigned int tail;

	/*
	 * We know the GPU must have read the request to have
	 * sent us the seqno + interrupt, so use the position
	 * of tail of the request to update the last known position
	 * of the GPU head.
	 *
	 * Note this requires that we are always called in request
	 * completion order.
	 */
	GEM_BUG_ON(!list_is_first(&request->ring_link, &ring->request_list));
	if (list_is_last(&request->ring_link, &ring->request_list)) {
		/*
		 * We may race here with execlists resubmitting this request
		 * as we retire it. The resubmission will move the ring->tail
		 * forwards (to request->wa_tail). We either read the
		 * current value that was written to hw, or the value that
		 * is just about to be. Either works, if we miss the last two
		 * noops - they are safe to be replayed on a reset.
		 */
		GEM_TRACE("marking %s as inactive\n", ring->timeline->name);
		tail = READ_ONCE(request->tail);
		list_del(&ring->active_link);
	} else {
		tail = request->postfix;
	}
	list_del_init(&request->ring_link);

	ring->head = tail;
}