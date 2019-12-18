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
struct tmio_mmc_host {int dummy; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 struct tmio_mmc_host* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  tmio_mmc_host_remove (struct tmio_mmc_host*) ; 
 int /*<<< orphan*/  uniphier_sd_clk_disable (struct tmio_mmc_host*) ; 

__attribute__((used)) static int uniphier_sd_remove(struct platform_device *pdev)
{
	struct tmio_mmc_host *host = platform_get_drvdata(pdev);

	tmio_mmc_host_remove(host);
	uniphier_sd_clk_disable(host);

	return 0;
}