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
struct sdhci_host {int dummy; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 struct sdhci_host* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  sdhci_free_host (struct sdhci_host*) ; 

void sdhci_pltfm_free(struct platform_device *pdev)
{
	struct sdhci_host *host = platform_get_drvdata(pdev);

	sdhci_free_host(host);
}