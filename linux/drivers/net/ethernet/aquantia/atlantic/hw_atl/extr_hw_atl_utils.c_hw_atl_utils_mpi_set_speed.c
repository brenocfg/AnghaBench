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
 int /*<<< orphan*/  HW_ATL_MPI_CONTROL_ADR ; 
 int HW_ATL_MPI_SPEED_MSK ; 
 int HW_ATL_MPI_SPEED_SHIFT ; 
 int aq_hw_read_reg (struct aq_hw_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aq_hw_write_reg (struct aq_hw_s*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hw_atl_utils_mpi_set_speed(struct aq_hw_s *self, u32 speed)
{
	u32 val = aq_hw_read_reg(self, HW_ATL_MPI_CONTROL_ADR);

	val = val & ~HW_ATL_MPI_SPEED_MSK;
	val |= speed << HW_ATL_MPI_SPEED_SHIFT;
	aq_hw_write_reg(self, HW_ATL_MPI_CONTROL_ADR, val);

	return 0;
}