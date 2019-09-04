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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct hw_aq_atl_utils_fw_rpc {int dummy; } ;
struct aq_hw_s {scalar_t__ rpc_tid; struct hw_aq_atl_utils_fw_rpc rpc; int /*<<< orphan*/  rpc_addr; } ;
struct aq_hw_atl_utils_fw_rpc_tid_s {scalar_t__ tid; int len; scalar_t__ val; } ;

/* Variables and functions */
 int /*<<< orphan*/  AQ_HW_WAIT_FOR (int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  HW_ATL_RPC_CONTROL_ADR ; 
 int /*<<< orphan*/  HW_ATL_RPC_STATE_ADR ; 
 void* aq_hw_read_reg (struct aq_hw_s*,int /*<<< orphan*/ ) ; 
 int hw_atl_utils_fw_downld_dwords (struct aq_hw_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int hw_atl_utils_fw_rpc_call (struct aq_hw_s*,int) ; 

__attribute__((used)) static int hw_atl_utils_fw_rpc_wait(struct aq_hw_s *self,
				    struct hw_aq_atl_utils_fw_rpc **rpc)
{
	int err = 0;
	struct aq_hw_atl_utils_fw_rpc_tid_s sw;
	struct aq_hw_atl_utils_fw_rpc_tid_s fw;

	do {
		sw.val = aq_hw_read_reg(self, HW_ATL_RPC_CONTROL_ADR);

		self->rpc_tid = sw.tid;

		AQ_HW_WAIT_FOR(sw.tid ==
				(fw.val =
				aq_hw_read_reg(self, HW_ATL_RPC_STATE_ADR),
				fw.tid), 1000U, 100U);
		if (err < 0)
			goto err_exit;

		if (fw.len == 0xFFFFU) {
			err = hw_atl_utils_fw_rpc_call(self, sw.len);
			if (err < 0)
				goto err_exit;
		}
	} while (sw.tid != fw.tid || 0xFFFFU == fw.len);
	if (err < 0)
		goto err_exit;

	if (rpc) {
		if (fw.len) {
			err =
			hw_atl_utils_fw_downld_dwords(self,
						      self->rpc_addr,
						      (u32 *)(void *)
						      &self->rpc,
						      (fw.len + sizeof(u32) -
						      sizeof(u8)) /
						      sizeof(u32));
			if (err < 0)
				goto err_exit;
		}

		*rpc = &self->rpc;
	}

err_exit:
	return err;
}