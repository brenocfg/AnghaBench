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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_4__ {int pattern_mask; } ;
struct hw_atl_utils_fw_rpc {TYPE_2__ msg_enable_wakeup; int /*<<< orphan*/  msg_id; } ;
struct aq_hw_s {TYPE_1__* aq_nic_cfg; } ;
struct TYPE_3__ {int wol; } ;

/* Variables and functions */
 int AQ_NIC_WOL_ENABLED ; 
 int /*<<< orphan*/  HAL_ATLANTIC_UTILS_FW_MSG_ENABLE_WAKEUP ; 
 int /*<<< orphan*/  MPI_POWER ; 
 int aq_fw1x_set_wol (struct aq_hw_s*,int,int /*<<< orphan*/ *) ; 
 int hw_atl_utils_fw_rpc_call (struct aq_hw_s*,unsigned int) ; 
 int hw_atl_utils_fw_rpc_wait (struct aq_hw_s*,struct hw_atl_utils_fw_rpc**) ; 
 int /*<<< orphan*/  hw_atl_utils_mpi_set_speed (struct aq_hw_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_atl_utils_mpi_set_state (struct aq_hw_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct hw_atl_utils_fw_rpc*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int aq_fw1x_set_power(struct aq_hw_s *self, unsigned int power_state,
			     u8 *mac)
{
	struct hw_atl_utils_fw_rpc *prpc = NULL;
	unsigned int rpc_size = 0U;
	int err = 0;

	if (self->aq_nic_cfg->wol & AQ_NIC_WOL_ENABLED) {
		err = aq_fw1x_set_wol(self, 1, mac);

		if (err < 0)
			goto err_exit;

		rpc_size = sizeof(prpc->msg_id) +
			   sizeof(prpc->msg_enable_wakeup);

		err = hw_atl_utils_fw_rpc_wait(self, &prpc);

		if (err < 0)
			goto err_exit;

		memset(prpc, 0, rpc_size);

		prpc->msg_id = HAL_ATLANTIC_UTILS_FW_MSG_ENABLE_WAKEUP;
		prpc->msg_enable_wakeup.pattern_mask = 0x00000002;

		err = hw_atl_utils_fw_rpc_call(self, rpc_size);
		if (err < 0)
			goto err_exit;
	}
	hw_atl_utils_mpi_set_speed(self, 0);
	hw_atl_utils_mpi_set_state(self, MPI_POWER);

err_exit:
	return err;
}