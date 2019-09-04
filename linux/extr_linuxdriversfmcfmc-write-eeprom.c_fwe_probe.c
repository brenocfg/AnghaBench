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
struct device {int dummy; } ;
struct fmc_device {struct device dev; } ;
struct firmware {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  busid_n; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOENT ; 
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,char*,...) ; 
 int dev_name (struct device*) ; 
 int fmc_validate (struct fmc_device*,TYPE_1__*) ; 
 TYPE_1__ fwe_drv ; 
 char** fwe_file ; 
 int fwe_file_n ; 
 int /*<<< orphan*/  fwe_run (struct fmc_device*,struct firmware const*,char*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char*,struct device*) ; 

__attribute__((used)) static int fwe_probe(struct fmc_device *fmc)
{
	int err, index = 0;
	const struct firmware *fw;
	struct device *dev = &fmc->dev;
	char *s;

	if (!fwe_drv.busid_n) {
		dev_err(dev, "%s: no busid passed, refusing all cards\n",
			KBUILD_MODNAME);
		return -ENODEV;
	}

	index = fmc_validate(fmc, &fwe_drv);
	if (index < 0) {
		pr_err("%s: refusing device \"%s\"\n", KBUILD_MODNAME,
		       dev_name(dev));
		return -ENODEV;
	}
	if (index >= fwe_file_n) {
		pr_err("%s: no filename for device index %i\n",
			KBUILD_MODNAME, index);
		return -ENODEV;
	}
	s = fwe_file[index];
	if (!s) {
		pr_err("%s: no filename for \"%s\" not programming\n",
		       KBUILD_MODNAME, dev_name(dev));
		return -ENOENT;
	}
	err = request_firmware(&fw, s, dev);
	if (err < 0) {
		dev_err(&fmc->dev, "request firmware \"%s\": error %i\n",
			s, err);
		return err;
	}
	fwe_run(fmc, fw, s);
	release_firmware(fw);
	return 0;
}