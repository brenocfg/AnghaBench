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
struct TYPE_2__ {scalar_t__ rmt_start; } ;
struct hfi1_devdata {TYPE_1__ vnic; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCV_CTRL_RCV_RSM_ENABLE_SMASK ; 
 int /*<<< orphan*/  RSM_INS_VNIC ; 
 int /*<<< orphan*/  clear_rcvctrl (struct hfi1_devdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_rsm_rule (struct hfi1_devdata*,int /*<<< orphan*/ ) ; 

void hfi1_deinit_vnic_rsm(struct hfi1_devdata *dd)
{
	clear_rsm_rule(dd, RSM_INS_VNIC);

	/* Disable RSM if used only by vnic */
	if (dd->vnic.rmt_start == 0)
		clear_rcvctrl(dd, RCV_CTRL_RCV_RSM_ENABLE_SMASK);
}