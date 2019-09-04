#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct s3cmci_host {int is2440; struct mmc_host* mmc; struct platform_device* pdev; } ;
struct s3c24xx_mci_pdata {int dummy; } ;
struct TYPE_3__ {struct s3c24xx_mci_pdata* platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;
struct mmc_host {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct s3c24xx_mci_pdata* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int mmc_of_parse (struct mmc_host*) ; 
 scalar_t__ of_device_get_match_data (TYPE_1__*) ; 

__attribute__((used)) static int s3cmci_probe_dt(struct s3cmci_host *host)
{
	struct platform_device *pdev = host->pdev;
	struct s3c24xx_mci_pdata *pdata;
	struct mmc_host *mmc = host->mmc;
	int ret;

	host->is2440 = (int) of_device_get_match_data(&pdev->dev);

	ret = mmc_of_parse(mmc);
	if (ret)
		return ret;

	pdata = devm_kzalloc(&pdev->dev, sizeof(*pdata), GFP_KERNEL);
	if (!pdata)
		return -ENOMEM;

	pdev->dev.platform_data = pdata;

	return 0;
}