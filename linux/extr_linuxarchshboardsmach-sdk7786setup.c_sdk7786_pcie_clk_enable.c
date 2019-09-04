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
struct clk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCIECR ; 
 int PCIECR_CLKEN ; 
 int fpga_read_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fpga_write_reg (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sdk7786_pcie_clk_enable(struct clk *clk)
{
	fpga_write_reg(fpga_read_reg(PCIECR) | PCIECR_CLKEN, PCIECR);
	return 0;
}