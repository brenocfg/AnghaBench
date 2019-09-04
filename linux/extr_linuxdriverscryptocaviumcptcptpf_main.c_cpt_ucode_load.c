#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct cpt_device {TYPE_1__* pdev; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int cpt_ucode_load_fw (struct cpt_device*,char*,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 

__attribute__((used)) static int cpt_ucode_load(struct cpt_device *cpt)
{
	int ret = 0;
	struct device *dev = &cpt->pdev->dev;

	ret = cpt_ucode_load_fw(cpt, "cpt8x-mc-ae.out", true);
	if (ret) {
		dev_err(dev, "ae:cpt_ucode_load failed with ret: %d\n", ret);
		return ret;
	}
	ret = cpt_ucode_load_fw(cpt, "cpt8x-mc-se.out", false);
	if (ret) {
		dev_err(dev, "se:cpt_ucode_load failed with ret: %d\n", ret);
		return ret;
	}

	return ret;
}