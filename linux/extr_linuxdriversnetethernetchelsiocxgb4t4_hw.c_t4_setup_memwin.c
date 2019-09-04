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
struct adapter {int dummy; } ;

/* Variables and functions */
 int BIR_V (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEMWIN0_APERTURE ; 
 int /*<<< orphan*/  PCIE_MEM_ACCESS_BASE_WIN_A ; 
 int /*<<< orphan*/  PCIE_MEM_ACCESS_REG (int /*<<< orphan*/ ,int) ; 
 scalar_t__ WINDOW_SHIFT_X ; 
 int WINDOW_V (scalar_t__) ; 
 scalar_t__ ilog2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_write_reg (struct adapter*,int /*<<< orphan*/ ,int) ; 

void t4_setup_memwin(struct adapter *adap, u32 memwin_base, u32 window)
{
	t4_write_reg(adap,
		     PCIE_MEM_ACCESS_REG(PCIE_MEM_ACCESS_BASE_WIN_A, window),
		     memwin_base | BIR_V(0) |
		     WINDOW_V(ilog2(MEMWIN0_APERTURE) - WINDOW_SHIFT_X));
	t4_read_reg(adap,
		    PCIE_MEM_ACCESS_REG(PCIE_MEM_ACCESS_BASE_WIN_A, window));
}