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
struct nvt_dev {int chip_major; int chip_minor; int /*<<< orphan*/  cr_efdr; int /*<<< orphan*/  cr_efir; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CR_CHIP_ID_HI ; 
 int /*<<< orphan*/  CR_CHIP_ID_LO ; 
 int /*<<< orphan*/  CR_EFDR2 ; 
 int /*<<< orphan*/  CR_EFIR2 ; 
 int ENODEV ; 
 int NVT_INVALID ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,char const*,int,int) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int,int) ; 
 void* nvt_cr_read (struct nvt_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvt_efm_disable (struct nvt_dev*) ; 
 int /*<<< orphan*/  nvt_efm_enable (struct nvt_dev*) ; 
 char* nvt_find_chip (struct nvt_dev*,int) ; 
 struct device* nvt_get_dev (struct nvt_dev*) ; 

__attribute__((used)) static int nvt_hw_detect(struct nvt_dev *nvt)
{
	struct device *dev = nvt_get_dev(nvt);
	const char *chip_name;
	int chip_id;

	nvt_efm_enable(nvt);

	/* Check if we're wired for the alternate EFER setup */
	nvt->chip_major = nvt_cr_read(nvt, CR_CHIP_ID_HI);
	if (nvt->chip_major == 0xff) {
		nvt_efm_disable(nvt);
		nvt->cr_efir = CR_EFIR2;
		nvt->cr_efdr = CR_EFDR2;
		nvt_efm_enable(nvt);
		nvt->chip_major = nvt_cr_read(nvt, CR_CHIP_ID_HI);
	}
	nvt->chip_minor = nvt_cr_read(nvt, CR_CHIP_ID_LO);

	nvt_efm_disable(nvt);

	chip_id = nvt->chip_major << 8 | nvt->chip_minor;
	if (chip_id == NVT_INVALID) {
		dev_err(dev, "No device found on either EFM port\n");
		return -ENODEV;
	}

	chip_name = nvt_find_chip(nvt, chip_id);

	/* warn, but still let the driver load, if we don't know this chip */
	if (!chip_name)
		dev_warn(dev,
			 "unknown chip, id: 0x%02x 0x%02x, it may not work...",
			 nvt->chip_major, nvt->chip_minor);
	else
		dev_info(dev, "found %s or compatible: chip id: 0x%02x 0x%02x",
			 chip_name, nvt->chip_major, nvt->chip_minor);

	return 0;
}