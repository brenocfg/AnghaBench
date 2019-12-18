#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  void* u32 ;
typedef  int u16 ;
struct priority_cos {int priority; size_t cos; } ;
struct bnx2x_func_tx_start_params {int dcb_enabled; int dont_add_pri_0_en; void** dcb_outer_pri; scalar_t__ dcb_version; struct priority_cos* traffic_type_to_priority_cos; } ;
struct TYPE_7__ {size_t num_of_cos; TYPE_2__* cos_params; } ;
struct TYPE_5__ {void** traffic_type_priority; } ;
struct TYPE_8__ {TYPE_3__ ets; TYPE_1__ app; } ;
struct bnx2x {int dcbx_error; TYPE_4__ dcbx_port_params; scalar_t__ dcb_version; } ;
struct TYPE_6__ {int pri_bitmask; } ;

/* Variables and functions */
 int DCBX_REMOTE_MIB_ERROR ; 
 int DRV_FLAGS_DCB_MFW_CONFIGURED ; 
 scalar_t__ GET_FLAGS (int /*<<< orphan*/ ,int) ; 
 size_t LLFC_DRIVER_TRAFFIC_TYPE_MAX ; 
 scalar_t__ SHMEM2_HAS (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHMEM2_RD (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_dcbx_print_cos_params (struct bnx2x*,struct bnx2x_func_tx_start_params*) ; 
 int /*<<< orphan*/  drv_flags ; 
 int /*<<< orphan*/  memset (struct bnx2x_func_tx_start_params*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void bnx2x_dcbx_fw_struct(struct bnx2x *bp,
				 struct bnx2x_func_tx_start_params *pfc_fw_cfg)
{
	u16 pri_bit = 0;
	u8 cos = 0, pri = 0;
	struct priority_cos *tt2cos;
	u32 *ttp = bp->dcbx_port_params.app.traffic_type_priority;
	int mfw_configured = SHMEM2_HAS(bp, drv_flags) &&
			     GET_FLAGS(SHMEM2_RD(bp, drv_flags),
				       1 << DRV_FLAGS_DCB_MFW_CONFIGURED);

	memset(pfc_fw_cfg, 0, sizeof(*pfc_fw_cfg));

	/* to disable DCB - the structure must be zeroed */
	if ((bp->dcbx_error & DCBX_REMOTE_MIB_ERROR) && !mfw_configured)
		return;

	/*shortcut*/
	tt2cos = pfc_fw_cfg->traffic_type_to_priority_cos;

	/* Fw version should be incremented each update */
	pfc_fw_cfg->dcb_version = ++bp->dcb_version;
	pfc_fw_cfg->dcb_enabled = 1;

	/* Fill priority parameters */
	for (pri = 0; pri < LLFC_DRIVER_TRAFFIC_TYPE_MAX; pri++) {
		tt2cos[pri].priority = ttp[pri];
		pri_bit = 1 << tt2cos[pri].priority;

		/* Fill COS parameters based on COS calculated to
		 * make it more general for future use */
		for (cos = 0; cos < bp->dcbx_port_params.ets.num_of_cos; cos++)
			if (bp->dcbx_port_params.ets.cos_params[cos].
						pri_bitmask & pri_bit)
					tt2cos[pri].cos = cos;

		pfc_fw_cfg->dcb_outer_pri[pri]  = ttp[pri];
	}

	/* we never want the FW to add a 0 vlan tag */
	pfc_fw_cfg->dont_add_pri_0_en = 1;

	bnx2x_dcbx_print_cos_params(bp,	pfc_fw_cfg);
}