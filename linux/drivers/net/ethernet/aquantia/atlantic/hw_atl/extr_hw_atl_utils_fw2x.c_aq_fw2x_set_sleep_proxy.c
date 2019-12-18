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
typedef  int u32 ;
struct offload_info {int len; int /*<<< orphan*/  mac_addr; } ;
struct hw_atl_utils_fw_rpc {int /*<<< orphan*/  msg_id; } ;
struct aq_hw_s {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int HW_ATL_FW2X_CTRL_LINK_DROP ; 
 int HW_ATL_FW2X_CTRL_SLEEP_PROXY ; 
 int /*<<< orphan*/  HW_ATL_FW2X_MPI_CONTROL2_ADDR ; 
 int /*<<< orphan*/  aq_fw2x_state2_get ; 
 int aq_hw_read_reg (struct aq_hw_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aq_hw_write_reg (struct aq_hw_s*,int /*<<< orphan*/ ,int) ; 
 int hw_atl_utils_fw_rpc_call (struct aq_hw_s*,unsigned int) ; 
 int hw_atl_utils_fw_rpc_wait (struct aq_hw_s*,struct hw_atl_utils_fw_rpc**) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct hw_atl_utils_fw_rpc*,int /*<<< orphan*/ ,unsigned int) ; 
 int readx_poll_timeout_atomic (int /*<<< orphan*/ ,struct aq_hw_s*,int,int,unsigned int,unsigned int) ; 

__attribute__((used)) static int aq_fw2x_set_sleep_proxy(struct aq_hw_s *self, u8 *mac)
{
	struct hw_atl_utils_fw_rpc *rpc = NULL;
	struct offload_info *cfg = NULL;
	unsigned int rpc_size = 0U;
	u32 mpi_opts;
	int err = 0;
	u32 val;

	rpc_size = sizeof(rpc->msg_id) + sizeof(*cfg);

	err = hw_atl_utils_fw_rpc_wait(self, &rpc);
	if (err < 0)
		goto err_exit;

	memset(rpc, 0, rpc_size);
	cfg = (struct offload_info *)(&rpc->msg_id + 1);

	memcpy(cfg->mac_addr, mac, ETH_ALEN);
	cfg->len = sizeof(*cfg);

	/* Clear bit 0x36C.23 and 0x36C.22 */
	mpi_opts = aq_hw_read_reg(self, HW_ATL_FW2X_MPI_CONTROL2_ADDR);
	mpi_opts &= ~HW_ATL_FW2X_CTRL_SLEEP_PROXY;
	mpi_opts &= ~HW_ATL_FW2X_CTRL_LINK_DROP;

	aq_hw_write_reg(self, HW_ATL_FW2X_MPI_CONTROL2_ADDR, mpi_opts);

	err = hw_atl_utils_fw_rpc_call(self, rpc_size);
	if (err < 0)
		goto err_exit;

	/* Set bit 0x36C.23 */
	mpi_opts |= HW_ATL_FW2X_CTRL_SLEEP_PROXY;
	aq_hw_write_reg(self, HW_ATL_FW2X_MPI_CONTROL2_ADDR, mpi_opts);

	err = readx_poll_timeout_atomic(aq_fw2x_state2_get,
					self, val,
					val & HW_ATL_FW2X_CTRL_SLEEP_PROXY,
					1U, 100000U);

err_exit:
	return err;
}