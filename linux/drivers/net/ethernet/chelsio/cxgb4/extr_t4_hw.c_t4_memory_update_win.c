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
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCIE_MEM_ACCESS_OFFSET_A ; 
 int /*<<< orphan*/  PCIE_MEM_ACCESS_REG (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_write_reg (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void t4_memory_update_win(struct adapter *adap, int win, u32 addr)
{
	t4_write_reg(adap,
		     PCIE_MEM_ACCESS_REG(PCIE_MEM_ACCESS_OFFSET_A, win),
		     addr);
	/* Read it back to ensure that changes propagate before we
	 * attempt to use the new value.
	 */
	t4_read_reg(adap,
		    PCIE_MEM_ACCESS_REG(PCIE_MEM_ACCESS_OFFSET_A, win));
}