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
typedef  int u32 ;
struct otg_fsm {int b_conn; int a_bus_req; int b_sess_vld; int a_bus_suspend; int a_conn; int b_bus_suspend; int /*<<< orphan*/  b_bus_req; TYPE_1__* otg; } ;
struct TYPE_4__ {int is_a_peripheral; } ;
struct ci_hdrc {TYPE_2__ gadget; int /*<<< orphan*/  driver; struct otg_fsm fsm; } ;
struct TYPE_3__ {int state; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_BIDL_ADIS ; 
 int /*<<< orphan*/  B_AIDL_BDIS ; 
 int /*<<< orphan*/  OP_PORTSC ; 
 int /*<<< orphan*/  OTGSC_BSV ; 
#define  OTG_STATE_A_HOST 135 
#define  OTG_STATE_A_PERIPHERAL 134 
#define  OTG_STATE_A_SUSPEND 133 
#define  OTG_STATE_A_WAIT_BCON 132 
#define  OTG_STATE_B_HOST 131 
#define  OTG_STATE_B_IDLE 130 
#define  OTG_STATE_B_PERIPHERAL 129 
#define  OTG_STATE_B_WAIT_ACON 128 
 int /*<<< orphan*/  PORTSC_CCS ; 
 int USBi_PCI ; 
 int USBi_SLI ; 
 int USBi_URI ; 
 int /*<<< orphan*/  ci_otg_add_timer (struct ci_hdrc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ci_otg_del_timer (struct ci_hdrc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ci_otg_queue_work (struct ci_hdrc*) ; 
 int hw_read (struct ci_hdrc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hw_read_intr_status (struct ci_hdrc*) ; 
 int hw_read_otgsc (struct ci_hdrc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ci_otg_fsm_event(struct ci_hdrc *ci)
{
	u32 intr_sts, otg_bsess_vld, port_conn;
	struct otg_fsm *fsm = &ci->fsm;

	intr_sts = hw_read_intr_status(ci);
	otg_bsess_vld = hw_read_otgsc(ci, OTGSC_BSV);
	port_conn = hw_read(ci, OP_PORTSC, PORTSC_CCS);

	switch (ci->fsm.otg->state) {
	case OTG_STATE_A_WAIT_BCON:
		if (port_conn) {
			fsm->b_conn = 1;
			fsm->a_bus_req = 1;
			ci_otg_queue_work(ci);
		}
		break;
	case OTG_STATE_B_IDLE:
		if (otg_bsess_vld && (intr_sts & USBi_PCI) && port_conn) {
			fsm->b_sess_vld = 1;
			ci_otg_queue_work(ci);
		}
		break;
	case OTG_STATE_B_PERIPHERAL:
		if ((intr_sts & USBi_SLI) && port_conn && otg_bsess_vld) {
			ci_otg_add_timer(ci, B_AIDL_BDIS);
		} else if (intr_sts & USBi_PCI) {
			ci_otg_del_timer(ci, B_AIDL_BDIS);
			if (fsm->a_bus_suspend == 1)
				fsm->a_bus_suspend = 0;
		}
		break;
	case OTG_STATE_B_HOST:
		if ((intr_sts & USBi_PCI) && !port_conn) {
			fsm->a_conn = 0;
			fsm->b_bus_req = 0;
			ci_otg_queue_work(ci);
		}
		break;
	case OTG_STATE_A_PERIPHERAL:
		if (intr_sts & USBi_SLI) {
			 fsm->b_bus_suspend = 1;
			/*
			 * Init a timer to know how long this suspend
			 * will continue, if time out, indicates B no longer
			 * wants to be host role
			 */
			 ci_otg_add_timer(ci, A_BIDL_ADIS);
		}

		if (intr_sts & USBi_URI)
			ci_otg_del_timer(ci, A_BIDL_ADIS);

		if (intr_sts & USBi_PCI) {
			if (fsm->b_bus_suspend == 1) {
				ci_otg_del_timer(ci, A_BIDL_ADIS);
				fsm->b_bus_suspend = 0;
			}
		}
		break;
	case OTG_STATE_A_SUSPEND:
		if ((intr_sts & USBi_PCI) && !port_conn) {
			fsm->b_conn = 0;

			/* if gadget driver is binded */
			if (ci->driver) {
				/* A device to be peripheral mode */
				ci->gadget.is_a_peripheral = 1;
			}
			ci_otg_queue_work(ci);
		}
		break;
	case OTG_STATE_A_HOST:
		if ((intr_sts & USBi_PCI) && !port_conn) {
			fsm->b_conn = 0;
			ci_otg_queue_work(ci);
		}
		break;
	case OTG_STATE_B_WAIT_ACON:
		if ((intr_sts & USBi_PCI) && port_conn) {
			fsm->a_conn = 1;
			ci_otg_queue_work(ci);
		}
		break;
	default:
		break;
	}
}