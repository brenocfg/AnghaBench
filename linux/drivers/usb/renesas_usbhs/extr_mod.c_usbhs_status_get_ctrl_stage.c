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
struct usbhs_irq_state {scalar_t__ intsts0; } ;

/* Variables and functions */
 int CTSQ_MASK ; 

int usbhs_status_get_ctrl_stage(struct usbhs_irq_state *irq_state)
{
	/*
	 * return value
	 *
	 * IDLE_SETUP_STAGE
	 * READ_DATA_STAGE
	 * READ_STATUS_STAGE
	 * WRITE_DATA_STAGE
	 * WRITE_STATUS_STAGE
	 * NODATA_STATUS_STAGE
	 * SEQUENCE_ERROR
	 */
	return (int)irq_state->intsts0 & CTSQ_MASK;
}