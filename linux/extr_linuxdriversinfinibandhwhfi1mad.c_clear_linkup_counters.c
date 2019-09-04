#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  status; } ;
struct TYPE_4__ {int /*<<< orphan*/  status_and_code; } ;
struct hfi1_devdata {TYPE_1__ err_info_xmit_constraint; scalar_t__ rcv_ovfl_cnt; TYPE_2__ err_info_rcvport; } ;

/* Variables and functions */
 int /*<<< orphan*/  CNTR_INVALID_VL ; 
 int /*<<< orphan*/  C_DC_RCV_ERR ; 
 int /*<<< orphan*/  C_DC_REINIT_FROM_PEER_CNT ; 
 int /*<<< orphan*/  C_DC_RX_REPLAY ; 
 int /*<<< orphan*/  C_DC_SEQ_CRC_CNT ; 
 int /*<<< orphan*/  C_RCV_OVF ; 
 int /*<<< orphan*/  OPA_EI_STATUS_SMASK ; 
 int /*<<< orphan*/  write_dev_cntr (struct hfi1_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void clear_linkup_counters(struct hfi1_devdata *dd)
{
	/* PortRcvErrors */
	write_dev_cntr(dd, C_DC_RCV_ERR, CNTR_INVALID_VL, 0);
	dd->err_info_rcvport.status_and_code &= ~OPA_EI_STATUS_SMASK;
	/* LinkErrorRecovery */
	write_dev_cntr(dd, C_DC_SEQ_CRC_CNT, CNTR_INVALID_VL, 0);
	write_dev_cntr(dd, C_DC_REINIT_FROM_PEER_CNT, CNTR_INVALID_VL, 0);
	/* LocalLinkIntegrityErrors */
	write_dev_cntr(dd, C_DC_RX_REPLAY, CNTR_INVALID_VL, 0);
	/* ExcessiveBufferOverruns */
	write_dev_cntr(dd, C_RCV_OVF, CNTR_INVALID_VL, 0);
	dd->rcv_ovfl_cnt = 0;
	dd->err_info_xmit_constraint.status &= ~OPA_EI_STATUS_SMASK;
}