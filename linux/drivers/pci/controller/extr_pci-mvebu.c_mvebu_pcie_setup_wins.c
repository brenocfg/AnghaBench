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
struct mvebu_pcie_port {int dummy; } ;
struct mbus_dram_window {int base; int size; int mbus_attr; } ;
struct mbus_dram_target_info {int num_cs; int mbus_dram_target_id; struct mbus_dram_window* cs; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCIE_BAR_CTRL_OFF (int) ; 
 int /*<<< orphan*/  PCIE_BAR_HI_OFF (int) ; 
 int /*<<< orphan*/  PCIE_BAR_LO_OFF (int) ; 
 int /*<<< orphan*/  PCIE_WIN04_BASE_OFF (int) ; 
 int /*<<< orphan*/  PCIE_WIN04_CTRL_OFF (int) ; 
 int /*<<< orphan*/  PCIE_WIN04_REMAP_OFF (int) ; 
 int /*<<< orphan*/  PCIE_WIN5_BASE_OFF ; 
 int /*<<< orphan*/  PCIE_WIN5_CTRL_OFF ; 
 int /*<<< orphan*/  PCIE_WIN5_REMAP_OFF ; 
 int fls (int) ; 
 struct mbus_dram_target_info* mv_mbus_dram_info () ; 
 int /*<<< orphan*/  mvebu_writel (struct mvebu_pcie_port*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mvebu_pcie_setup_wins(struct mvebu_pcie_port *port)
{
	const struct mbus_dram_target_info *dram;
	u32 size;
	int i;

	dram = mv_mbus_dram_info();

	/* First, disable and clear BARs and windows. */
	for (i = 1; i < 3; i++) {
		mvebu_writel(port, 0, PCIE_BAR_CTRL_OFF(i));
		mvebu_writel(port, 0, PCIE_BAR_LO_OFF(i));
		mvebu_writel(port, 0, PCIE_BAR_HI_OFF(i));
	}

	for (i = 0; i < 5; i++) {
		mvebu_writel(port, 0, PCIE_WIN04_CTRL_OFF(i));
		mvebu_writel(port, 0, PCIE_WIN04_BASE_OFF(i));
		mvebu_writel(port, 0, PCIE_WIN04_REMAP_OFF(i));
	}

	mvebu_writel(port, 0, PCIE_WIN5_CTRL_OFF);
	mvebu_writel(port, 0, PCIE_WIN5_BASE_OFF);
	mvebu_writel(port, 0, PCIE_WIN5_REMAP_OFF);

	/* Setup windows for DDR banks.  Count total DDR size on the fly. */
	size = 0;
	for (i = 0; i < dram->num_cs; i++) {
		const struct mbus_dram_window *cs = dram->cs + i;

		mvebu_writel(port, cs->base & 0xffff0000,
			     PCIE_WIN04_BASE_OFF(i));
		mvebu_writel(port, 0, PCIE_WIN04_REMAP_OFF(i));
		mvebu_writel(port,
			     ((cs->size - 1) & 0xffff0000) |
			     (cs->mbus_attr << 8) |
			     (dram->mbus_dram_target_id << 4) | 1,
			     PCIE_WIN04_CTRL_OFF(i));

		size += cs->size;
	}

	/* Round up 'size' to the nearest power of two. */
	if ((size & (size - 1)) != 0)
		size = 1 << fls(size);

	/* Setup BAR[1] to all DRAM banks. */
	mvebu_writel(port, dram->cs[0].base, PCIE_BAR_LO_OFF(1));
	mvebu_writel(port, 0, PCIE_BAR_HI_OFF(1));
	mvebu_writel(port, ((size - 1) & 0xffff0000) | 1,
		     PCIE_BAR_CTRL_OFF(1));
}