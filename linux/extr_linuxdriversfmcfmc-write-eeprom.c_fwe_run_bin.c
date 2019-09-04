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
struct fmc_device {int /*<<< orphan*/  dev; } ;
struct firmware {int /*<<< orphan*/  size; scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 int fmc_write_ee (struct fmc_device*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fwe_run_bin(struct fmc_device *fmc, const struct firmware *fw)
{
	int ret;

	dev_info(&fmc->dev, "programming %zi bytes\n", fw->size);
	ret = fmc_write_ee(fmc, 0, (void *)fw->data, fw->size);
	if (ret < 0) {
		dev_info(&fmc->dev, "write_eeprom: error %i\n", ret);
		return ret;
	}
	dev_info(&fmc->dev, "write_eeprom: success\n");
	return 0;
}