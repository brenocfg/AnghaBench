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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  write; int /*<<< orphan*/ * dev; } ;
struct nvmem_reboot_mode {TYPE_1__ reboot; int /*<<< orphan*/  cell; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct nvmem_reboot_mode* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_nvmem_cell_get (int /*<<< orphan*/ *,char*) ; 
 int devm_reboot_mode_register (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  nvmem_reboot_mode_write ; 

__attribute__((used)) static int nvmem_reboot_mode_probe(struct platform_device *pdev)
{
	int ret;
	struct nvmem_reboot_mode *nvmem_rbm;

	nvmem_rbm = devm_kzalloc(&pdev->dev, sizeof(*nvmem_rbm), GFP_KERNEL);
	if (!nvmem_rbm)
		return -ENOMEM;

	nvmem_rbm->reboot.dev = &pdev->dev;
	nvmem_rbm->reboot.write = nvmem_reboot_mode_write;

	nvmem_rbm->cell = devm_nvmem_cell_get(&pdev->dev, "reboot-mode");
	if (IS_ERR(nvmem_rbm->cell)) {
		dev_err(&pdev->dev, "failed to get the nvmem cell reboot-mode\n");
		return PTR_ERR(nvmem_rbm->cell);
	}

	ret = devm_reboot_mode_register(&pdev->dev, &nvmem_rbm->reboot);
	if (ret)
		dev_err(&pdev->dev, "can't register reboot mode\n");

	return ret;
}