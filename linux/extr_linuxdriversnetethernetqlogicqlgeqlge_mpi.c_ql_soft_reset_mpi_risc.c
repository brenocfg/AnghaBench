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
struct ql_adapter {int dummy; } ;

/* Variables and functions */
 int ql_write_mpi_reg (struct ql_adapter*,int,int) ; 

int ql_soft_reset_mpi_risc(struct ql_adapter *qdev)
{
	int status;
	status = ql_write_mpi_reg(qdev, 0x00001010, 1);
	return status;
}