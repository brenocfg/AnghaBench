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
 int /*<<< orphan*/  CSR ; 
 int /*<<< orphan*/  CSR_CMD_CLR_PAUSE ; 
 int CSR_RP ; 
 int EIO ; 
 int ql_read32 (struct ql_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_write32 (struct ql_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ql_unpause_mpi_risc(struct ql_adapter *qdev)
{
	u32 tmp;

	/* Un-pause the RISC */
	tmp = ql_read32(qdev, CSR);
	if (!(tmp & CSR_RP))
		return -EIO;

	ql_write32(qdev, CSR, CSR_CMD_CLR_PAUSE);
	return 0;
}