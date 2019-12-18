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
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct rvt_dev_info {int dummy; } ;
struct ib_port_attr {int active_width; int active_speed; void* max_mtu; void* active_mtu; int /*<<< orphan*/  max_vl_num; int /*<<< orphan*/  gid_tbl_len; int /*<<< orphan*/  phys_state; int /*<<< orphan*/  state; int /*<<< orphan*/  lmc; scalar_t__ lid; } ;
struct hfi1_pportdata {int ibmtu; int /*<<< orphan*/  vls_supported; int /*<<< orphan*/  link_speed_active; int /*<<< orphan*/  link_width_active; int /*<<< orphan*/  lmc; scalar_t__ lid; } ;
struct hfi1_ibdev {int dummy; } ;
struct hfi1_devdata {struct hfi1_pportdata* pport; } ;

/* Variables and functions */
 int /*<<< orphan*/  HFI1_GUIDS_PER_PORT ; 
 int /*<<< orphan*/  IB_MTU_4096 ; 
 struct hfi1_devdata* dd_from_dev (struct hfi1_ibdev*) ; 
 struct hfi1_ibdev* dev_from_rdi (struct rvt_dev_info*) ; 
 int /*<<< orphan*/  driver_lstate (struct hfi1_pportdata*) ; 
 int /*<<< orphan*/  driver_pstate (struct hfi1_pportdata*) ; 
 int hfi1_max_mtu ; 
 void* mtu_to_enum (int,int /*<<< orphan*/ ) ; 
 scalar_t__ opa_speed_to_ib (int /*<<< orphan*/ ) ; 
 scalar_t__ opa_width_to_ib (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  valid_ib_mtu (int) ; 

__attribute__((used)) static int query_port(struct rvt_dev_info *rdi, u8 port_num,
		      struct ib_port_attr *props)
{
	struct hfi1_ibdev *verbs_dev = dev_from_rdi(rdi);
	struct hfi1_devdata *dd = dd_from_dev(verbs_dev);
	struct hfi1_pportdata *ppd = &dd->pport[port_num - 1];
	u32 lid = ppd->lid;

	/* props being zeroed by the caller, avoid zeroing it here */
	props->lid = lid ? lid : 0;
	props->lmc = ppd->lmc;
	/* OPA logical states match IB logical states */
	props->state = driver_lstate(ppd);
	props->phys_state = driver_pstate(ppd);
	props->gid_tbl_len = HFI1_GUIDS_PER_PORT;
	props->active_width = (u8)opa_width_to_ib(ppd->link_width_active);
	/* see rate_show() in ib core/sysfs.c */
	props->active_speed = (u8)opa_speed_to_ib(ppd->link_speed_active);
	props->max_vl_num = ppd->vls_supported;

	/* Once we are a "first class" citizen and have added the OPA MTUs to
	 * the core we can advertise the larger MTU enum to the ULPs, for now
	 * advertise only 4K.
	 *
	 * Those applications which are either OPA aware or pass the MTU enum
	 * from the Path Records to us will get the new 8k MTU.  Those that
	 * attempt to process the MTU enum may fail in various ways.
	 */
	props->max_mtu = mtu_to_enum((!valid_ib_mtu(hfi1_max_mtu) ?
				      4096 : hfi1_max_mtu), IB_MTU_4096);
	props->active_mtu = !valid_ib_mtu(ppd->ibmtu) ? props->max_mtu :
		mtu_to_enum(ppd->ibmtu, IB_MTU_4096);

	return 0;
}