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
struct vxge_fifo {scalar_t__ interrupt_count; scalar_t__ jiffies; struct __vxge_hw_fifo* handle; } ;
struct __vxge_hw_fifo {scalar_t__ rtimer; } ;

/* Variables and functions */
 int HZ ; 
 scalar_t__ VXGE_T1A_MAX_TX_INTERRUPT_COUNT ; 
 scalar_t__ VXGE_TTI_RTIMER_ADAPT_VAL ; 
 scalar_t__ jiffies ; 
 scalar_t__ time_before (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  vxge_hw_vpath_dynamic_tti_rtimer_set (struct __vxge_hw_fifo*) ; 

__attribute__((used)) static void adaptive_coalesce_tx_interrupts(struct vxge_fifo *fifo)
{
	fifo->interrupt_count++;
	if (time_before(fifo->jiffies + HZ / 100, jiffies)) {
		struct __vxge_hw_fifo *hw_fifo = fifo->handle;

		fifo->jiffies = jiffies;
		if (fifo->interrupt_count > VXGE_T1A_MAX_TX_INTERRUPT_COUNT &&
		    hw_fifo->rtimer != VXGE_TTI_RTIMER_ADAPT_VAL) {
			hw_fifo->rtimer = VXGE_TTI_RTIMER_ADAPT_VAL;
			vxge_hw_vpath_dynamic_tti_rtimer_set(hw_fifo);
		} else if (hw_fifo->rtimer != 0) {
			hw_fifo->rtimer = 0;
			vxge_hw_vpath_dynamic_tti_rtimer_set(hw_fifo);
		}
		fifo->interrupt_count = 0;
	}
}