#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct llcc_slice_config {scalar_t__ slice_id; } ;
struct TYPE_6__ {int num_banks; scalar_t__ max_slices; int* offsets; int cfg_size; scalar_t__ ecc_irq; int /*<<< orphan*/  lock; struct llcc_slice_config const* cfg; void* bitmap; struct platform_device* regmap; struct platform_device* bcast_regmap; } ;

/* Variables and functions */
 int BANK_OFFSET_STRIDE ; 
 int BITS_TO_LONGS (scalar_t__) ; 
 int /*<<< orphan*/  ENODEV ; 
 int ENOMEM ; 
 TYPE_1__* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct platform_device*) ; 
 int /*<<< orphan*/  LLCC_COMMON_STATUS0 ; 
 int LLCC_LB_CNT_MASK ; 
 int LLCC_LB_CNT_SHIFT ; 
 int PTR_ERR (struct platform_device*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 void* devm_kcalloc (struct device*,int,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* drv_data ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct platform_device* platform_device_register_data (struct device*,char*,int,TYPE_1__*,int) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,TYPE_1__*) ; 
 int qcom_llcc_cfg_program (struct platform_device*) ; 
 void* qcom_llcc_init_mmio (struct platform_device*,char*) ; 
 int regmap_read (struct platform_device*,int /*<<< orphan*/ ,int*) ; 

int qcom_llcc_probe(struct platform_device *pdev,
		      const struct llcc_slice_config *llcc_cfg, u32 sz)
{
	u32 num_banks;
	struct device *dev = &pdev->dev;
	int ret, i;
	struct platform_device *llcc_edac;

	drv_data = devm_kzalloc(dev, sizeof(*drv_data), GFP_KERNEL);
	if (!drv_data) {
		ret = -ENOMEM;
		goto err;
	}

	drv_data->regmap = qcom_llcc_init_mmio(pdev, "llcc_base");
	if (IS_ERR(drv_data->regmap)) {
		ret = PTR_ERR(drv_data->regmap);
		goto err;
	}

	drv_data->bcast_regmap =
		qcom_llcc_init_mmio(pdev, "llcc_broadcast_base");
	if (IS_ERR(drv_data->bcast_regmap)) {
		ret = PTR_ERR(drv_data->bcast_regmap);
		goto err;
	}

	ret = regmap_read(drv_data->regmap, LLCC_COMMON_STATUS0,
						&num_banks);
	if (ret)
		goto err;

	num_banks &= LLCC_LB_CNT_MASK;
	num_banks >>= LLCC_LB_CNT_SHIFT;
	drv_data->num_banks = num_banks;

	for (i = 0; i < sz; i++)
		if (llcc_cfg[i].slice_id > drv_data->max_slices)
			drv_data->max_slices = llcc_cfg[i].slice_id;

	drv_data->offsets = devm_kcalloc(dev, num_banks, sizeof(u32),
							GFP_KERNEL);
	if (!drv_data->offsets) {
		ret = -ENOMEM;
		goto err;
	}

	for (i = 0; i < num_banks; i++)
		drv_data->offsets[i] = i * BANK_OFFSET_STRIDE;

	drv_data->bitmap = devm_kcalloc(dev,
	BITS_TO_LONGS(drv_data->max_slices), sizeof(unsigned long),
						GFP_KERNEL);
	if (!drv_data->bitmap) {
		ret = -ENOMEM;
		goto err;
	}

	drv_data->cfg = llcc_cfg;
	drv_data->cfg_size = sz;
	mutex_init(&drv_data->lock);
	platform_set_drvdata(pdev, drv_data);

	ret = qcom_llcc_cfg_program(pdev);
	if (ret)
		goto err;

	drv_data->ecc_irq = platform_get_irq(pdev, 0);
	if (drv_data->ecc_irq >= 0) {
		llcc_edac = platform_device_register_data(&pdev->dev,
						"qcom_llcc_edac", -1, drv_data,
						sizeof(*drv_data));
		if (IS_ERR(llcc_edac))
			dev_err(dev, "Failed to register llcc edac driver\n");
	}

	return 0;
err:
	drv_data = ERR_PTR(-ENODEV);
	return ret;
}