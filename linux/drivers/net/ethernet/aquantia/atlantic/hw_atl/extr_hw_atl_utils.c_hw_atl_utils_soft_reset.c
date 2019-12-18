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
typedef  int u32 ;
struct aq_hw_s {int rbl_enabled; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  HW_ATL_FW_VER_1X ; 
 int /*<<< orphan*/  HW_ATL_MPI_BOOT_EXIT_CODE ; 
 int /*<<< orphan*/  HW_ATL_MPI_DAISY_CHAIN_STATUS ; 
 int /*<<< orphan*/  HW_ATL_MPI_FW_VERSION ; 
 int HW_ATL_MPI_STATE_MSK ; 
 int MPI_DEINIT ; 
 int aq_hw_read_reg (struct aq_hw_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aq_pr_err (char*) ; 
 int /*<<< orphan*/  hw_atl_utils_mpi_get_state ; 
 int /*<<< orphan*/  hw_atl_utils_mpi_set_state (struct aq_hw_s*,int) ; 
 int hw_atl_utils_soft_reset_flb (struct aq_hw_s*) ; 
 int hw_atl_utils_soft_reset_rbl (struct aq_hw_s*) ; 
 int /*<<< orphan*/  hw_atl_utils_ver_match (int /*<<< orphan*/ ,int) ; 
 int readx_poll_timeout_atomic (int /*<<< orphan*/ ,struct aq_hw_s*,int,int,int,unsigned int) ; 

int hw_atl_utils_soft_reset(struct aq_hw_s *self)
{
	int k;
	u32 boot_exit_code = 0;
	u32 val;

	for (k = 0; k < 1000; ++k) {
		u32 flb_status = aq_hw_read_reg(self,
						HW_ATL_MPI_DAISY_CHAIN_STATUS);
		boot_exit_code = aq_hw_read_reg(self,
						HW_ATL_MPI_BOOT_EXIT_CODE);
		if (flb_status != 0x06000000 || boot_exit_code != 0)
			break;
	}

	if (k == 1000) {
		aq_pr_err("Neither RBL nor FLB firmware started\n");
		return -EOPNOTSUPP;
	}

	self->rbl_enabled = (boot_exit_code != 0);

	/* FW 1.x may bootup in an invalid POWER state (WOL feature).
	 * We should work around this by forcing its state back to DEINIT
	 */
	if (!hw_atl_utils_ver_match(HW_ATL_FW_VER_1X,
				    aq_hw_read_reg(self,
						   HW_ATL_MPI_FW_VERSION))) {
		int err = 0;

		hw_atl_utils_mpi_set_state(self, MPI_DEINIT);
		err = readx_poll_timeout_atomic(hw_atl_utils_mpi_get_state,
						self, val,
						(val & HW_ATL_MPI_STATE_MSK) ==
						 MPI_DEINIT,
						10, 10000U);
		if (err)
			return err;
	}

	if (self->rbl_enabled)
		return hw_atl_utils_soft_reset_rbl(self);
	else
		return hw_atl_utils_soft_reset_flb(self);
}