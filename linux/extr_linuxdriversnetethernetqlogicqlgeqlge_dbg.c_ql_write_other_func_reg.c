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
struct ql_adapter {int alt_func; } ;

/* Variables and functions */
 int MPI_NIC_FUNCTION_SHIFT ; 
 int MPI_NIC_READ ; 
 int MPI_NIC_REG_BLOCK ; 
 int ql_write_mpi_reg (struct ql_adapter*,int,int) ; 

__attribute__((used)) static int ql_write_other_func_reg(struct ql_adapter *qdev,
					u32 reg, u32 reg_val)
{
	u32 register_to_read;
	int status = 0;

	register_to_read = MPI_NIC_REG_BLOCK
				| MPI_NIC_READ
				| (qdev->alt_func << MPI_NIC_FUNCTION_SHIFT)
				| reg;
	status = ql_write_mpi_reg(qdev, register_to_read, reg_val);

	return status;
}