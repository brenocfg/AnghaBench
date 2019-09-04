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
struct platform_device {int dummy; } ;
struct mmc_pwrseq_emmc {int /*<<< orphan*/  pwrseq; int /*<<< orphan*/  reset_nb; } ;

/* Variables and functions */
 int /*<<< orphan*/  mmc_pwrseq_unregister (int /*<<< orphan*/ *) ; 
 struct mmc_pwrseq_emmc* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  unregister_restart_handler (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mmc_pwrseq_emmc_remove(struct platform_device *pdev)
{
	struct mmc_pwrseq_emmc *pwrseq = platform_get_drvdata(pdev);

	unregister_restart_handler(&pwrseq->reset_nb);
	mmc_pwrseq_unregister(&pwrseq->pwrseq);

	return 0;
}