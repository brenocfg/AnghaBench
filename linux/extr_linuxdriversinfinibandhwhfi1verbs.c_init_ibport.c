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
struct TYPE_4__ {int port_cap_flags; int /*<<< orphan*/ * qp; int /*<<< orphan*/ * pma_counter_select; int /*<<< orphan*/  port_cap3_flags; scalar_t__ sm_lid; int /*<<< orphan*/  gid_prefix; int /*<<< orphan*/  lock; int /*<<< orphan*/  trap_timer; TYPE_1__* trap_lists; } ;
struct hfi1_ibport {int* sl_to_sc; int* sc_to_sl; TYPE_2__ rvp; } ;
struct hfi1_pportdata {struct hfi1_ibport ibport_data; } ;
struct TYPE_3__ {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  IB_DEFAULT_GID_PREFIX ; 
 int /*<<< orphan*/  IB_PMA_PORT_RCV_DATA ; 
 int /*<<< orphan*/  IB_PMA_PORT_RCV_PKTS ; 
 int /*<<< orphan*/  IB_PMA_PORT_XMIT_DATA ; 
 int /*<<< orphan*/  IB_PMA_PORT_XMIT_PKTS ; 
 int /*<<< orphan*/  IB_PMA_PORT_XMIT_WAIT ; 
 int IB_PORT_AUTO_MIGR_SUP ; 
 int IB_PORT_CAP_MASK_NOTICE_SUP ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPA_CAP_MASK3_IsSharedSpaceSupported ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int RVT_MAX_TRAP_LISTS ; 
 int /*<<< orphan*/  hfi1_handle_trap_timer ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void init_ibport(struct hfi1_pportdata *ppd)
{
	struct hfi1_ibport *ibp = &ppd->ibport_data;
	size_t sz = ARRAY_SIZE(ibp->sl_to_sc);
	int i;

	for (i = 0; i < sz; i++) {
		ibp->sl_to_sc[i] = i;
		ibp->sc_to_sl[i] = i;
	}

	for (i = 0; i < RVT_MAX_TRAP_LISTS ; i++)
		INIT_LIST_HEAD(&ibp->rvp.trap_lists[i].list);
	timer_setup(&ibp->rvp.trap_timer, hfi1_handle_trap_timer, 0);

	spin_lock_init(&ibp->rvp.lock);
	/* Set the prefix to the default value (see ch. 4.1.1) */
	ibp->rvp.gid_prefix = IB_DEFAULT_GID_PREFIX;
	ibp->rvp.sm_lid = 0;
	/*
	 * Below should only set bits defined in OPA PortInfo.CapabilityMask
	 * and PortInfo.CapabilityMask3
	 */
	ibp->rvp.port_cap_flags = IB_PORT_AUTO_MIGR_SUP |
		IB_PORT_CAP_MASK_NOTICE_SUP;
	ibp->rvp.port_cap3_flags = OPA_CAP_MASK3_IsSharedSpaceSupported;
	ibp->rvp.pma_counter_select[0] = IB_PMA_PORT_XMIT_DATA;
	ibp->rvp.pma_counter_select[1] = IB_PMA_PORT_RCV_DATA;
	ibp->rvp.pma_counter_select[2] = IB_PMA_PORT_XMIT_PKTS;
	ibp->rvp.pma_counter_select[3] = IB_PMA_PORT_RCV_PKTS;
	ibp->rvp.pma_counter_select[4] = IB_PMA_PORT_XMIT_WAIT;

	RCU_INIT_POINTER(ibp->rvp.qp[0], NULL);
	RCU_INIT_POINTER(ibp->rvp.qp[1], NULL);
}