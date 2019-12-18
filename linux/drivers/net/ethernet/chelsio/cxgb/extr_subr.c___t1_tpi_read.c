#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {scalar_t__ regs; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ adapter_t ;

/* Variables and functions */
 scalar_t__ A_TPI_ADDR ; 
 scalar_t__ A_TPI_CSR ; 
 scalar_t__ A_TPI_RD_DATA ; 
 int /*<<< orphan*/  F_TPIRDY ; 
 int /*<<< orphan*/  TPI_ATTEMPTS ; 
 int /*<<< orphan*/  pr_alert (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int t1_wait_op_done (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

int __t1_tpi_read(adapter_t *adapter, u32 addr, u32 *valp)
{
	int tpi_busy;

	writel(addr, adapter->regs + A_TPI_ADDR);
	writel(0, adapter->regs + A_TPI_CSR);

	tpi_busy = t1_wait_op_done(adapter, A_TPI_CSR, F_TPIRDY, 1,
				   TPI_ATTEMPTS, 3);
	if (tpi_busy)
		pr_alert("%s: TPI read from 0x%x failed\n",
			 adapter->name, addr);
	else
		*valp = readl(adapter->regs + A_TPI_RD_DATA);
	return tpi_busy;
}