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
typedef  int /*<<< orphan*/  u32 ;
struct aq_hw_s {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HW_ATL_FW2X_MPI_CONTROL2_ADDR ; 
 int /*<<< orphan*/  aq_fw2x_upd_eee_rate_bits (struct aq_hw_s*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aq_hw_read_reg (struct aq_hw_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aq_hw_write_reg (struct aq_hw_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int aq_fw2x_set_eee_rate(struct aq_hw_s *self, u32 speed)
{
	u32 mpi_opts = aq_hw_read_reg(self, HW_ATL_FW2X_MPI_CONTROL2_ADDR);

	aq_fw2x_upd_eee_rate_bits(self, &mpi_opts, speed);

	aq_hw_write_reg(self, HW_ATL_FW2X_MPI_CONTROL2_ADDR, mpi_opts);

	return 0;
}