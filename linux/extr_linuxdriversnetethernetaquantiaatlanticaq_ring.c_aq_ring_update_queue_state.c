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
struct aq_ring_s {int dummy; } ;

/* Variables and functions */
 scalar_t__ AQ_CFG_RESTART_DESC_THRES ; 
 scalar_t__ AQ_CFG_SKB_FRAGS_MAX ; 
 scalar_t__ aq_ring_avail_dx (struct aq_ring_s*) ; 
 int /*<<< orphan*/  aq_ring_queue_stop (struct aq_ring_s*) ; 
 int /*<<< orphan*/  aq_ring_queue_wake (struct aq_ring_s*) ; 

void aq_ring_update_queue_state(struct aq_ring_s *ring)
{
	if (aq_ring_avail_dx(ring) <= AQ_CFG_SKB_FRAGS_MAX)
		aq_ring_queue_stop(ring);
	else if (aq_ring_avail_dx(ring) > AQ_CFG_RESTART_DESC_THRES)
		aq_ring_queue_wake(ring);
}