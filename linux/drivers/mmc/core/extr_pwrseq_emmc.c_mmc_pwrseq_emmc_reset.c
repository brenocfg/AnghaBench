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
struct mmc_pwrseq_emmc {int /*<<< orphan*/  reset_gpio; } ;
struct mmc_host {int /*<<< orphan*/  pwrseq; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 struct mmc_pwrseq_emmc* to_pwrseq_emmc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void mmc_pwrseq_emmc_reset(struct mmc_host *host)
{
	struct mmc_pwrseq_emmc *pwrseq =  to_pwrseq_emmc(host->pwrseq);

	gpiod_set_value_cansleep(pwrseq->reset_gpio, 1);
	udelay(1);
	gpiod_set_value_cansleep(pwrseq->reset_gpio, 0);
	udelay(200);
}