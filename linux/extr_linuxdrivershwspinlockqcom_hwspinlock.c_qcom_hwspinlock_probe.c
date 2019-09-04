#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct regmap {int dummy; } ;
struct reg_field {int reg; int msb; scalar_t__ lsb; } ;
struct TYPE_9__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct hwspinlock_device {TYPE_1__* lock; } ;
struct hwspinlock {int dummy; } ;
struct device_node {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  priv; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 int QCOM_MUTEX_NUM_LOCKS ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 struct hwspinlock_device* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_field_alloc (TYPE_2__*,struct regmap*,struct reg_field) ; 
 int hwspin_lock_register (struct hwspinlock_device*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int of_property_read_u32_index (int /*<<< orphan*/ ,char*,int,int*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct hwspinlock_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_2__*) ; 
 int /*<<< orphan*/  qcom_hwspinlock_ops ; 
 struct regmap* syscon_node_to_regmap (struct device_node*) ; 

__attribute__((used)) static int qcom_hwspinlock_probe(struct platform_device *pdev)
{
	struct hwspinlock_device *bank;
	struct device_node *syscon;
	struct reg_field field;
	struct regmap *regmap;
	size_t array_size;
	u32 stride;
	u32 base;
	int ret;
	int i;

	syscon = of_parse_phandle(pdev->dev.of_node, "syscon", 0);
	if (!syscon) {
		dev_err(&pdev->dev, "no syscon property\n");
		return -ENODEV;
	}

	regmap = syscon_node_to_regmap(syscon);
	of_node_put(syscon);
	if (IS_ERR(regmap))
		return PTR_ERR(regmap);

	ret = of_property_read_u32_index(pdev->dev.of_node, "syscon", 1, &base);
	if (ret < 0) {
		dev_err(&pdev->dev, "no offset in syscon\n");
		return -EINVAL;
	}

	ret = of_property_read_u32_index(pdev->dev.of_node, "syscon", 2, &stride);
	if (ret < 0) {
		dev_err(&pdev->dev, "no stride syscon\n");
		return -EINVAL;
	}

	array_size = QCOM_MUTEX_NUM_LOCKS * sizeof(struct hwspinlock);
	bank = devm_kzalloc(&pdev->dev, sizeof(*bank) + array_size, GFP_KERNEL);
	if (!bank)
		return -ENOMEM;

	platform_set_drvdata(pdev, bank);

	for (i = 0; i < QCOM_MUTEX_NUM_LOCKS; i++) {
		field.reg = base + i * stride;
		field.lsb = 0;
		field.msb = 31;

		bank->lock[i].priv = devm_regmap_field_alloc(&pdev->dev,
							     regmap, field);
	}

	pm_runtime_enable(&pdev->dev);

	ret = hwspin_lock_register(bank, &pdev->dev, &qcom_hwspinlock_ops,
				   0, QCOM_MUTEX_NUM_LOCKS);
	if (ret)
		pm_runtime_disable(&pdev->dev);

	return ret;
}