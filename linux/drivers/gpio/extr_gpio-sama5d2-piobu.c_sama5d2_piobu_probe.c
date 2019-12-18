#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int base; int ngpio; scalar_t__ can_sleep; int /*<<< orphan*/  set; int /*<<< orphan*/  get; int /*<<< orphan*/  direction_output; int /*<<< orphan*/  direction_input; int /*<<< orphan*/  get_direction; int /*<<< orphan*/  owner; int /*<<< orphan*/  of_node; TYPE_2__* parent; int /*<<< orphan*/  label; } ;
struct sama5d2_piobu {TYPE_1__ chip; int /*<<< orphan*/  regmap; } ;
struct TYPE_7__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_2__ dev; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PIOBU_NUM ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,int,...) ; 
 int devm_gpiochip_add_data (TYPE_2__*,TYPE_1__*,struct sama5d2_piobu*) ; 
 struct sama5d2_piobu* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct sama5d2_piobu*) ; 
 int /*<<< orphan*/  sama5d2_piobu_direction_input ; 
 int /*<<< orphan*/  sama5d2_piobu_direction_output ; 
 int /*<<< orphan*/  sama5d2_piobu_get ; 
 int /*<<< orphan*/  sama5d2_piobu_get_direction ; 
 int /*<<< orphan*/  sama5d2_piobu_set ; 
 int sama5d2_piobu_setup_pin (TYPE_1__*,int) ; 
 int /*<<< orphan*/  syscon_node_to_regmap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sama5d2_piobu_probe(struct platform_device *pdev)
{
	struct sama5d2_piobu *piobu;
	int ret, i;

	piobu = devm_kzalloc(&pdev->dev, sizeof(*piobu), GFP_KERNEL);
	if (!piobu)
		return -ENOMEM;

	platform_set_drvdata(pdev, piobu);
	piobu->chip.label = pdev->name;
	piobu->chip.parent = &pdev->dev;
	piobu->chip.of_node = pdev->dev.of_node;
	piobu->chip.owner = THIS_MODULE,
	piobu->chip.get_direction = sama5d2_piobu_get_direction,
	piobu->chip.direction_input = sama5d2_piobu_direction_input,
	piobu->chip.direction_output = sama5d2_piobu_direction_output,
	piobu->chip.get = sama5d2_piobu_get,
	piobu->chip.set = sama5d2_piobu_set,
	piobu->chip.base = -1,
	piobu->chip.ngpio = PIOBU_NUM,
	piobu->chip.can_sleep = 0,

	piobu->regmap = syscon_node_to_regmap(pdev->dev.of_node);
	if (IS_ERR(piobu->regmap)) {
		dev_err(&pdev->dev, "Failed to get syscon regmap %ld\n",
			PTR_ERR(piobu->regmap));
		return PTR_ERR(piobu->regmap);
	}

	ret = devm_gpiochip_add_data(&pdev->dev, &piobu->chip, piobu);
	if (ret) {
		dev_err(&pdev->dev, "Failed to add gpiochip %d\n", ret);
		return ret;
	}

	for (i = 0; i < PIOBU_NUM; ++i) {
		ret = sama5d2_piobu_setup_pin(&piobu->chip, i);
		if (ret) {
			dev_err(&pdev->dev, "Failed to setup pin: %d %d\n",
				i, ret);
			return ret;
		}
	}

	return 0;
}