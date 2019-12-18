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
struct vxge_ring {scalar_t__ interrupt_count; scalar_t__ jiffies; struct __vxge_hw_ring* handle; } ;
struct __vxge_hw_ring {scalar_t__ rtimer; } ;

/* Variables and functions */
 int HZ ; 
 scalar_t__ VXGE_RTI_RTIMER_ADAPT_VAL ; 
 scalar_t__ VXGE_T1A_MAX_INTERRUPT_COUNT ; 
 scalar_t__ jiffies ; 
 scalar_t__ time_before (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  vxge_hw_vpath_dynamic_rti_rtimer_set (struct __vxge_hw_ring*) ; 

__attribute__((used)) static void adaptive_coalesce_rx_interrupts(struct vxge_ring *ring)
{
	ring->interrupt_count++;
	if (time_before(ring->jiffies + HZ / 100, jiffies)) {
		struct __vxge_hw_ring *hw_ring = ring->handle;

		ring->jiffies = jiffies;
		if (ring->interrupt_count > VXGE_T1A_MAX_INTERRUPT_COUNT &&
		    hw_ring->rtimer != VXGE_RTI_RTIMER_ADAPT_VAL) {
			hw_ring->rtimer = VXGE_RTI_RTIMER_ADAPT_VAL;
			vxge_hw_vpath_dynamic_rti_rtimer_set(hw_ring);
		} else if (hw_ring->rtimer != 0) {
			hw_ring->rtimer = 0;
			vxge_hw_vpath_dynamic_rti_rtimer_set(hw_ring);
		}
		ring->interrupt_count = 0;
	}
}