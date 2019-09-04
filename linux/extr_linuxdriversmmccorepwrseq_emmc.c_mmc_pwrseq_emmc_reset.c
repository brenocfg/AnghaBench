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
struct mmc_pwrseq_emmc {int dummy; } ;
struct mmc_host {int /*<<< orphan*/  pwrseq; } ;

/* Variables and functions */
 int /*<<< orphan*/  __mmc_pwrseq_emmc_reset (struct mmc_pwrseq_emmc*) ; 
 struct mmc_pwrseq_emmc* to_pwrseq_emmc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mmc_pwrseq_emmc_reset(struct mmc_host *host)
{
	struct mmc_pwrseq_emmc *pwrseq =  to_pwrseq_emmc(host->pwrseq);

	__mmc_pwrseq_emmc_reset(pwrseq);
}