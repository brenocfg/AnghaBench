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
struct ql_adapter {int dummy; } ;

/* Variables and functions */
 int MPI_CORE_SH_REGS_CNT ; 
 int /*<<< orphan*/  RISC_124 ; 
 int /*<<< orphan*/  RISC_127 ; 
 int SHADOW_OFFSET ; 
 int SHADOW_REG_SHIFT ; 
 int ql_read_mpi_reg (struct ql_adapter*,int /*<<< orphan*/ ,int*) ; 
 int ql_write_mpi_reg (struct ql_adapter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ql_get_mpi_shadow_regs(struct ql_adapter *qdev, u32 *buf)
{
	u32 i;
	int status;

	for (i = 0; i < MPI_CORE_SH_REGS_CNT; i++, buf++) {
		status = ql_write_mpi_reg(qdev, RISC_124,
				(SHADOW_OFFSET | i << SHADOW_REG_SHIFT));
		if (status)
			goto end;
		status = ql_read_mpi_reg(qdev, RISC_127, buf);
		if (status)
			goto end;
	}
end:
	return status;
}