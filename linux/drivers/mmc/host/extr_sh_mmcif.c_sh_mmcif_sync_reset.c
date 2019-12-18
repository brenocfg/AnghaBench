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
struct sh_mmcif_host {int /*<<< orphan*/  addr; scalar_t__ clk_ctrl2_enable; scalar_t__ ccs_enable; } ;

/* Variables and functions */
 int BUF_ACC_ATYP ; 
 int /*<<< orphan*/  MMCIF_CE_BUF_ACC ; 
 int /*<<< orphan*/  MMCIF_CE_CLK_CTRL ; 
 int /*<<< orphan*/  MMCIF_CE_CLK_CTRL2 ; 
 int /*<<< orphan*/  MMCIF_CE_VERSION ; 
 int SCCSTO_29 ; 
 int SOFT_RST_OFF ; 
 int SOFT_RST_ON ; 
 int SRBSYTO_29 ; 
 int SRSPTO_256 ; 
 int SRWDTO_29 ; 
 int /*<<< orphan*/  sh_mmcif_bitset (struct sh_mmcif_host*,int /*<<< orphan*/ ,int) ; 
 int sh_mmcif_readl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sh_mmcif_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sh_mmcif_sync_reset(struct sh_mmcif_host *host)
{
	u32 tmp;

	tmp = 0x010f0000 & sh_mmcif_readl(host->addr, MMCIF_CE_CLK_CTRL);

	sh_mmcif_writel(host->addr, MMCIF_CE_VERSION, SOFT_RST_ON);
	sh_mmcif_writel(host->addr, MMCIF_CE_VERSION, SOFT_RST_OFF);
	if (host->ccs_enable)
		tmp |= SCCSTO_29;
	if (host->clk_ctrl2_enable)
		sh_mmcif_writel(host->addr, MMCIF_CE_CLK_CTRL2, 0x0F0F0000);
	sh_mmcif_bitset(host, MMCIF_CE_CLK_CTRL, tmp |
		SRSPTO_256 | SRBSYTO_29 | SRWDTO_29);
	/* byte swap on */
	sh_mmcif_bitset(host, MMCIF_CE_BUF_ACC, BUF_ACC_ATYP);
}