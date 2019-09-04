#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_7__ {int adf2; } ;
struct TYPE_10__ {int conf; int /*<<< orphan*/  (* write_reg ) (struct inf_hw*,int /*<<< orphan*/ ,int) ;TYPE_3__* hscx; TYPE_2__ isac; } ;
struct TYPE_9__ {int /*<<< orphan*/  start; scalar_t__ p; } ;
struct inf_hw {TYPE_5__ ipac; TYPE_4__ cfg; TYPE_1__* ci; int /*<<< orphan*/  name; } ;
struct TYPE_8__ {int slot; } ;
struct TYPE_6__ {int typ; } ;

/* Variables and functions */
 int DEBUG_HW ; 
 int DIVA_LED_A ; 
 scalar_t__ DIVA_PCI_CTRL ; 
 int DIVA_RESET_BIT ; 
 scalar_t__ GAZEL_CNTRL ; 
 scalar_t__ GAZEL_RESET ; 
 scalar_t__ GAZEL_RESET_9050 ; 
#define  INF_DIVA20 139 
#define  INF_DIVA201 138 
#define  INF_DIVA202 137 
#define  INF_DIVA20U 136 
#define  INF_GAZEL_R685 135 
#define  INF_GAZEL_R753 134 
#define  INF_NICCY 133 
#define  INF_QS1000 132 
#define  INF_QS3000 131 
#define  INF_SAPHIR3 130 
#define  INF_SCT_1 129 
#define  INF_SPEEDWIN 128 
 int /*<<< orphan*/  IPAC_ACFG ; 
 int /*<<< orphan*/  IPAC_AOE ; 
 int /*<<< orphan*/  IPAC_ATX ; 
 int /*<<< orphan*/  IPAC_PCFG ; 
 scalar_t__ PITA_MISC_REG ; 
 int PITA_PARA_MPX_MODE ; 
 int PITA_PARA_SOFTRESET ; 
 int PITA_SER_SOFTRESET ; 
 scalar_t__ SCT_PLX_RESET_ADDR ; 
 int /*<<< orphan*/  SCT_PLX_RESET_BIT ; 
 int debug ; 
 int /*<<< orphan*/  enable_hwirq (struct inf_hw*) ; 
 scalar_t__ inl (scalar_t__) ; 
 int /*<<< orphan*/  inw (scalar_t__) ; 
 int /*<<< orphan*/  ipac_chip_reset (struct inf_hw*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  outl (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  outw (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pr_notice (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct inf_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (struct inf_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (struct inf_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub4 (struct inf_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub5 (struct inf_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub6 (struct inf_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub7 (struct inf_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub8 (struct inf_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void
reset_inf(struct inf_hw *hw)
{
	u16 w;
	u32 val;

	if (debug & DEBUG_HW)
		pr_notice("%s: resetting card\n", hw->name);
	switch (hw->ci->typ) {
	case INF_DIVA20:
	case INF_DIVA20U:
		outb(0, (u32)hw->cfg.start + DIVA_PCI_CTRL);
		mdelay(10);
		outb(DIVA_RESET_BIT, (u32)hw->cfg.start + DIVA_PCI_CTRL);
		mdelay(10);
		/* Workaround PCI9060 */
		outb(9, (u32)hw->cfg.start + 0x69);
		outb(DIVA_RESET_BIT | DIVA_LED_A,
		     (u32)hw->cfg.start + DIVA_PCI_CTRL);
		break;
	case INF_DIVA201:
		writel(PITA_PARA_SOFTRESET | PITA_PARA_MPX_MODE,
		       hw->cfg.p + PITA_MISC_REG);
		mdelay(1);
		writel(PITA_PARA_MPX_MODE, hw->cfg.p + PITA_MISC_REG);
		mdelay(10);
		break;
	case INF_DIVA202:
		writel(PITA_PARA_SOFTRESET | PITA_PARA_MPX_MODE,
		       hw->cfg.p + PITA_MISC_REG);
		mdelay(1);
		writel(PITA_PARA_MPX_MODE | PITA_SER_SOFTRESET,
		       hw->cfg.p + PITA_MISC_REG);
		mdelay(10);
		break;
	case INF_SPEEDWIN:
	case INF_SAPHIR3:
		ipac_chip_reset(hw);
		hw->ipac.write_reg(hw, IPAC_ACFG, 0xff);
		hw->ipac.write_reg(hw, IPAC_AOE, 0x00);
		hw->ipac.write_reg(hw, IPAC_PCFG, 0x12);
		break;
	case INF_QS1000:
	case INF_QS3000:
		ipac_chip_reset(hw);
		hw->ipac.write_reg(hw, IPAC_ACFG, 0x00);
		hw->ipac.write_reg(hw, IPAC_AOE, 0x3c);
		hw->ipac.write_reg(hw, IPAC_ATX, 0xff);
		break;
	case INF_NICCY:
		break;
	case INF_SCT_1:
		w = inw((u32)hw->cfg.start + SCT_PLX_RESET_ADDR);
		w &= (~SCT_PLX_RESET_BIT);
		outw(w, (u32)hw->cfg.start + SCT_PLX_RESET_ADDR);
		mdelay(10);
		w = inw((u32)hw->cfg.start + SCT_PLX_RESET_ADDR);
		w |= SCT_PLX_RESET_BIT;
		outw(w, (u32)hw->cfg.start + SCT_PLX_RESET_ADDR);
		mdelay(10);
		break;
	case INF_GAZEL_R685:
		val = inl((u32)hw->cfg.start + GAZEL_CNTRL);
		val |= (GAZEL_RESET_9050 + GAZEL_RESET);
		outl(val, (u32)hw->cfg.start + GAZEL_CNTRL);
		val &= ~(GAZEL_RESET_9050 + GAZEL_RESET);
		mdelay(4);
		outl(val, (u32)hw->cfg.start + GAZEL_CNTRL);
		mdelay(10);
		hw->ipac.isac.adf2 = 0x87;
		hw->ipac.hscx[0].slot = 0x1f;
		hw->ipac.hscx[1].slot = 0x23;
		break;
	case INF_GAZEL_R753:
		val = inl((u32)hw->cfg.start + GAZEL_CNTRL);
		val |= (GAZEL_RESET_9050 + GAZEL_RESET);
		outl(val, (u32)hw->cfg.start + GAZEL_CNTRL);
		val &= ~(GAZEL_RESET_9050 + GAZEL_RESET);
		mdelay(4);
		outl(val, (u32)hw->cfg.start + GAZEL_CNTRL);
		mdelay(10);
		ipac_chip_reset(hw);
		hw->ipac.write_reg(hw, IPAC_ACFG, 0xff);
		hw->ipac.write_reg(hw, IPAC_AOE, 0x00);
		hw->ipac.conf = 0x01; /* IOM off */
		break;
	default:
		return;
	}
	enable_hwirq(hw);
}