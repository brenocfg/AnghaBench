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
struct fmc_driver {int dummy; } ;
struct fmc_device {int /*<<< orphan*/  flags; int /*<<< orphan*/  dev; } ;
struct firmware {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FMC_DEVICE_HAS_CUSTOM ; 
 int /*<<< orphan*/  FMC_DEVICE_HAS_GOLDEN ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,char*,int) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ff_reprogram(struct fmc_device *fmc, struct fmc_driver *drv,
			  char *gw)
{
	const struct firmware *fw;
	int ret;

	if (!gw) {
		/* program golden: success */
		fmc->flags &= ~FMC_DEVICE_HAS_CUSTOM;
		fmc->flags |= FMC_DEVICE_HAS_GOLDEN;
		return 0;
	}

	dev_info(&fmc->dev, "reprogramming with %s\n", gw);
	ret = request_firmware(&fw, gw, &fmc->dev);
	if (ret < 0) {
		dev_warn(&fmc->dev, "request firmware \"%s\": error %i\n",
			 gw, ret);
		goto out;
	}
	fmc->flags &= ~FMC_DEVICE_HAS_GOLDEN;
	fmc->flags |= FMC_DEVICE_HAS_CUSTOM;

out:
	release_firmware(fw);
	return ret;
}