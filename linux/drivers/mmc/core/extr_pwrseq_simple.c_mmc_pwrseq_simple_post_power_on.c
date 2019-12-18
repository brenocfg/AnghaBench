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
struct mmc_pwrseq_simple {scalar_t__ post_power_on_delay_ms; } ;
struct mmc_host {int /*<<< orphan*/  pwrseq; } ;

/* Variables and functions */
 int /*<<< orphan*/  mmc_pwrseq_simple_set_gpios_value (struct mmc_pwrseq_simple*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (scalar_t__) ; 
 struct mmc_pwrseq_simple* to_pwrseq_simple (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mmc_pwrseq_simple_post_power_on(struct mmc_host *host)
{
	struct mmc_pwrseq_simple *pwrseq = to_pwrseq_simple(host->pwrseq);

	mmc_pwrseq_simple_set_gpios_value(pwrseq, 0);

	if (pwrseq->post_power_on_delay_ms)
		msleep(pwrseq->post_power_on_delay_ms);
}