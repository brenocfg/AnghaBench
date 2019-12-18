#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sc27xx_efuse {int /*<<< orphan*/  hwlock; TYPE_1__* dev; int /*<<< orphan*/  mutex; int /*<<< orphan*/  base; int /*<<< orphan*/  regmap; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct nvmem_device {int dummy; } ;
struct nvmem_config {int stride; int word_size; int read_only; char* name; int size; TYPE_1__* dev; struct sc27xx_efuse* priv; int /*<<< orphan*/  reg_read; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct nvmem_device*) ; 
 int PTR_ERR (struct nvmem_device*) ; 
 int SC27XX_EFUSE_BLOCK_MAX ; 
 int SC27XX_EFUSE_BLOCK_WIDTH ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_get_regmap (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct sc27xx_efuse* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 struct nvmem_device* devm_nvmem_register (TYPE_1__*,struct nvmem_config*) ; 
 int /*<<< orphan*/  hwspin_lock_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwspin_lock_request_specific (int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int of_hwspin_lock_get_id (struct device_node*,int /*<<< orphan*/ ) ; 
 int of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct sc27xx_efuse*) ; 
 int /*<<< orphan*/  sc27xx_efuse_read ; 

__attribute__((used)) static int sc27xx_efuse_probe(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	struct nvmem_config econfig = { };
	struct nvmem_device *nvmem;
	struct sc27xx_efuse *efuse;
	int ret;

	efuse = devm_kzalloc(&pdev->dev, sizeof(*efuse), GFP_KERNEL);
	if (!efuse)
		return -ENOMEM;

	efuse->regmap = dev_get_regmap(pdev->dev.parent, NULL);
	if (!efuse->regmap) {
		dev_err(&pdev->dev, "failed to get efuse regmap\n");
		return -ENODEV;
	}

	ret = of_property_read_u32(np, "reg", &efuse->base);
	if (ret) {
		dev_err(&pdev->dev, "failed to get efuse base address\n");
		return ret;
	}

	ret = of_hwspin_lock_get_id(np, 0);
	if (ret < 0) {
		dev_err(&pdev->dev, "failed to get hwspinlock id\n");
		return ret;
	}

	efuse->hwlock = hwspin_lock_request_specific(ret);
	if (!efuse->hwlock) {
		dev_err(&pdev->dev, "failed to request hwspinlock\n");
		return -ENXIO;
	}

	mutex_init(&efuse->mutex);
	efuse->dev = &pdev->dev;
	platform_set_drvdata(pdev, efuse);

	econfig.stride = 1;
	econfig.word_size = 1;
	econfig.read_only = true;
	econfig.name = "sc27xx-efuse";
	econfig.size = SC27XX_EFUSE_BLOCK_MAX * SC27XX_EFUSE_BLOCK_WIDTH;
	econfig.reg_read = sc27xx_efuse_read;
	econfig.priv = efuse;
	econfig.dev = &pdev->dev;
	nvmem = devm_nvmem_register(&pdev->dev, &econfig);
	if (IS_ERR(nvmem)) {
		dev_err(&pdev->dev, "failed to register nvmem config\n");
		hwspin_lock_free(efuse->hwlock);
		return PTR_ERR(nvmem);
	}

	return 0;
}