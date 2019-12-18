#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct tegra_kbc {int mmio; TYPE_1__* pin_cfg; } ;
struct TYPE_2__ {int type; int num; } ;

/* Variables and functions */
 int KBC_COL_CFG0_0 ; 
 int KBC_MAX_GPIO ; 
 int KBC_ROW_CFG0_0 ; 
#define  PIN_CFG_COL 130 
#define  PIN_CFG_IGNORE 129 
#define  PIN_CFG_ROW 128 
 int readl (int) ; 
 int /*<<< orphan*/  writel (int,int) ; 

__attribute__((used)) static void tegra_kbc_config_pins(struct tegra_kbc *kbc)
{
	int i;

	for (i = 0; i < KBC_MAX_GPIO; i++) {
		u32 r_shft = 5 * (i % 6);
		u32 c_shft = 4 * (i % 8);
		u32 r_mask = 0x1f << r_shft;
		u32 c_mask = 0x0f << c_shft;
		u32 r_offs = (i / 6) * 4 + KBC_ROW_CFG0_0;
		u32 c_offs = (i / 8) * 4 + KBC_COL_CFG0_0;
		u32 row_cfg = readl(kbc->mmio + r_offs);
		u32 col_cfg = readl(kbc->mmio + c_offs);

		row_cfg &= ~r_mask;
		col_cfg &= ~c_mask;

		switch (kbc->pin_cfg[i].type) {
		case PIN_CFG_ROW:
			row_cfg |= ((kbc->pin_cfg[i].num << 1) | 1) << r_shft;
			break;

		case PIN_CFG_COL:
			col_cfg |= ((kbc->pin_cfg[i].num << 1) | 1) << c_shft;
			break;

		case PIN_CFG_IGNORE:
			break;
		}

		writel(row_cfg, kbc->mmio + r_offs);
		writel(col_cfg, kbc->mmio + c_offs);
	}
}