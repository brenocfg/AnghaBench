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

/* Variables and functions */
 int /*<<< orphan*/  sdhci_cns3xxx_pdata ; 
 int sdhci_pltfm_register (struct platform_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sdhci_cns3xxx_probe(struct platform_device *pdev)
{
	return sdhci_pltfm_register(pdev, &sdhci_cns3xxx_pdata, 0);
}