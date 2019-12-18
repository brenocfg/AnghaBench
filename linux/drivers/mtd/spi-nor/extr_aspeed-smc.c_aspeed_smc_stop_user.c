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
struct spi_nor {struct aspeed_smc_chip* priv; } ;
struct aspeed_smc_chip {int* ctl_val; int /*<<< orphan*/  ctl; } ;

/* Variables and functions */
 int CONTROL_CE_STOP_ACTIVE_CONTROL ; 
 int CONTROL_COMMAND_MODE_USER ; 
 size_t smc_read ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void aspeed_smc_stop_user(struct spi_nor *nor)
{
	struct aspeed_smc_chip *chip = nor->priv;

	u32 ctl = chip->ctl_val[smc_read];
	u32 ctl2 = ctl | CONTROL_COMMAND_MODE_USER |
		CONTROL_CE_STOP_ACTIVE_CONTROL;

	writel(ctl2, chip->ctl);	/* stop user CE control */
	writel(ctl, chip->ctl);		/* default to fread or read mode */
}