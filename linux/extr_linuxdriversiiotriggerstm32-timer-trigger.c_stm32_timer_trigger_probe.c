#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct stm32_timers {int /*<<< orphan*/  max_arr; int /*<<< orphan*/  clk; int /*<<< orphan*/  regmap; } ;
struct stm32_timer_trigger_cfg {unsigned int num_valids_table; scalar_t__** valids_table; } ;
struct stm32_timer_trigger {scalar_t__* valids; int /*<<< orphan*/  triggers; int /*<<< orphan*/  max_arr; int /*<<< orphan*/  clk; int /*<<< orphan*/  regmap; struct device* dev; } ;
struct device {TYPE_1__* driver; int /*<<< orphan*/  of_node; int /*<<< orphan*/  parent; } ;
struct platform_device {struct device dev; } ;
struct TYPE_4__ {scalar_t__ data; } ;
struct TYPE_3__ {int /*<<< orphan*/  of_match_table; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct stm32_timers* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct stm32_timer_trigger* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 TYPE_2__* of_match_device (int /*<<< orphan*/ ,struct device*) ; 
 scalar_t__ of_property_read_u32 (int /*<<< orphan*/ ,char*,unsigned int*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct stm32_timer_trigger*) ; 
 struct stm32_timer_trigger* stm32_setup_counter_device (struct device*) ; 
 int stm32_setup_iio_triggers (struct stm32_timer_trigger*) ; 
 int /*<<< orphan*/  stm32_timer_detect_trgo2 (struct stm32_timer_trigger*) ; 
 int /*<<< orphan*/ * triggers_table ; 

__attribute__((used)) static int stm32_timer_trigger_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct stm32_timer_trigger *priv;
	struct stm32_timers *ddata = dev_get_drvdata(pdev->dev.parent);
	const struct stm32_timer_trigger_cfg *cfg;
	unsigned int index;
	int ret;

	if (of_property_read_u32(dev->of_node, "reg", &index))
		return -EINVAL;

	cfg = (const struct stm32_timer_trigger_cfg *)
		of_match_device(dev->driver->of_match_table, dev)->data;

	if (index >= ARRAY_SIZE(triggers_table) ||
	    index >= cfg->num_valids_table)
		return -EINVAL;

	/* Create an IIO device only if we have triggers to be validated */
	if (*cfg->valids_table[index])
		priv = stm32_setup_counter_device(dev);
	else
		priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);

	if (!priv)
		return -ENOMEM;

	priv->dev = dev;
	priv->regmap = ddata->regmap;
	priv->clk = ddata->clk;
	priv->max_arr = ddata->max_arr;
	priv->triggers = triggers_table[index];
	priv->valids = cfg->valids_table[index];
	stm32_timer_detect_trgo2(priv);

	ret = stm32_setup_iio_triggers(priv);
	if (ret)
		return ret;

	platform_set_drvdata(pdev, priv);

	return 0;
}