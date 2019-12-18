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
struct aq_hw_s {int dummy; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CAPS_HI_STATISTICS ; 
 int /*<<< orphan*/  HW_ATL_FW2X_MPI_CONTROL2_ADDR ; 
 int /*<<< orphan*/  aq_fw2x_state2_get ; 
 int aq_hw_read_reg (struct aq_hw_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aq_hw_write_reg (struct aq_hw_s*,int /*<<< orphan*/ ,int) ; 
 int hw_atl_utils_update_stats (struct aq_hw_s*) ; 
 int readx_poll_timeout_atomic (int /*<<< orphan*/ ,struct aq_hw_s*,int,int,unsigned int,unsigned int) ; 

__attribute__((used)) static int aq_fw2x_update_stats(struct aq_hw_s *self)
{
	int err = 0;
	u32 mpi_opts = aq_hw_read_reg(self, HW_ATL_FW2X_MPI_CONTROL2_ADDR);
	u32 orig_stats_val = mpi_opts & BIT(CAPS_HI_STATISTICS);
	u32 stats_val;

	/* Toggle statistics bit for FW to update */
	mpi_opts = mpi_opts ^ BIT(CAPS_HI_STATISTICS);
	aq_hw_write_reg(self, HW_ATL_FW2X_MPI_CONTROL2_ADDR, mpi_opts);

	/* Wait FW to report back */
	err = readx_poll_timeout_atomic(aq_fw2x_state2_get,
					self, stats_val,
					orig_stats_val != (stats_val &
					BIT(CAPS_HI_STATISTICS)),
					1U, 10000U);
	if (err)
		return err;

	return hw_atl_utils_update_stats(self);
}