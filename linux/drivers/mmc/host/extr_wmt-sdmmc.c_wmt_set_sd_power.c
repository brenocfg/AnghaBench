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
struct wmt_mci_priv {int power_inverted; scalar_t__ sdmmc_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  BM_SD_OFF ; 
 scalar_t__ SDMMC_BUSMODE ; 
 int /*<<< orphan*/  readb (scalar_t__) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void wmt_set_sd_power(struct wmt_mci_priv *priv, int enable)
{
	u32 reg_tmp = readb(priv->sdmmc_base + SDMMC_BUSMODE);

	if (enable ^ priv->power_inverted)
		reg_tmp &= ~BM_SD_OFF;
	else
		reg_tmp |= BM_SD_OFF;

	writeb(reg_tmp, priv->sdmmc_base + SDMMC_BUSMODE);
}