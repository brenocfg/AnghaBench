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
struct wmt_mci_priv {scalar_t__ sdmmc_base; } ;

/* Variables and functions */
 int CTLR_CMD_START ; 
 scalar_t__ SDMMC_CTLR ; 
 int readb (scalar_t__) ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 

__attribute__((used)) static void wmt_mci_start_command(struct wmt_mci_priv *priv)
{
	u32 reg_tmp;

	reg_tmp = readb(priv->sdmmc_base + SDMMC_CTLR);
	writeb(reg_tmp | CTLR_CMD_START, priv->sdmmc_base + SDMMC_CTLR);
}