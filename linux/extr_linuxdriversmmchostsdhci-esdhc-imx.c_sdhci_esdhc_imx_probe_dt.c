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
struct pltfm_imx_data {int dummy; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 

__attribute__((used)) static inline int
sdhci_esdhc_imx_probe_dt(struct platform_device *pdev,
			 struct sdhci_host *host,
			 struct pltfm_imx_data *imx_data)
{
	return -ENODEV;
}