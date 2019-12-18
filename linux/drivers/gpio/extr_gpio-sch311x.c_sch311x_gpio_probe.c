#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sch311x_pdev_data {scalar_t__ runtime_reg; } ;
struct sch311x_gpio_priv {struct sch311x_gpio_block* blocks; } ;
struct TYPE_5__ {int ngpio; int /*<<< orphan*/  base; int /*<<< orphan*/ * parent; int /*<<< orphan*/  set; int /*<<< orphan*/  get; int /*<<< orphan*/  set_config; int /*<<< orphan*/  get_direction; int /*<<< orphan*/  direction_output; int /*<<< orphan*/  direction_input; int /*<<< orphan*/  free; int /*<<< orphan*/  request; int /*<<< orphan*/  owner; int /*<<< orphan*/  label; } ;
struct sch311x_gpio_block {TYPE_2__ chip; scalar_t__ runtime_reg; int /*<<< orphan*/  data_reg; int /*<<< orphan*/  config_regs; int /*<<< orphan*/  lock; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  data_reg; int /*<<< orphan*/  config_regs; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct sch311x_gpio_block*) ; 
 int /*<<< orphan*/  DRV_NAME ; 
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ GP1 ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,...) ; 
 struct sch311x_pdev_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int) ; 
 struct sch311x_gpio_priv* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_request_region (int /*<<< orphan*/ *,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int gpiochip_add_data (TYPE_2__*,struct sch311x_gpio_block*) ; 
 int /*<<< orphan*/  gpiochip_remove (TYPE_2__*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct sch311x_gpio_priv*) ; 
 TYPE_1__* sch311x_gpio_blocks ; 
 int /*<<< orphan*/  sch311x_gpio_direction_in ; 
 int /*<<< orphan*/  sch311x_gpio_direction_out ; 
 int /*<<< orphan*/  sch311x_gpio_free ; 
 int /*<<< orphan*/  sch311x_gpio_get ; 
 int /*<<< orphan*/  sch311x_gpio_get_direction ; 
 int /*<<< orphan*/  sch311x_gpio_request ; 
 int /*<<< orphan*/  sch311x_gpio_set ; 
 int /*<<< orphan*/  sch311x_gpio_set_config ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sch311x_gpio_probe(struct platform_device *pdev)
{
	struct sch311x_pdev_data *pdata = dev_get_platdata(&pdev->dev);
	struct sch311x_gpio_priv *priv;
	struct sch311x_gpio_block *block;
	int err, i;

	/* we can register all GPIO data registers at once */
	if (!devm_request_region(&pdev->dev, pdata->runtime_reg + GP1, 6,
		DRV_NAME)) {
		dev_err(&pdev->dev, "Failed to request region 0x%04x-0x%04x.\n",
			pdata->runtime_reg + GP1, pdata->runtime_reg + GP1 + 5);
		return -EBUSY;
	}

	priv = devm_kzalloc(&pdev->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	platform_set_drvdata(pdev, priv);

	for (i = 0; i < ARRAY_SIZE(priv->blocks); i++) {
		block = &priv->blocks[i];

		spin_lock_init(&block->lock);

		block->chip.label = DRV_NAME;
		block->chip.owner = THIS_MODULE;
		block->chip.request = sch311x_gpio_request;
		block->chip.free = sch311x_gpio_free;
		block->chip.direction_input = sch311x_gpio_direction_in;
		block->chip.direction_output = sch311x_gpio_direction_out;
		block->chip.get_direction = sch311x_gpio_get_direction;
		block->chip.set_config = sch311x_gpio_set_config;
		block->chip.get = sch311x_gpio_get;
		block->chip.set = sch311x_gpio_set;
		block->chip.ngpio = 8;
		block->chip.parent = &pdev->dev;
		block->chip.base = sch311x_gpio_blocks[i].base;
		block->config_regs = sch311x_gpio_blocks[i].config_regs;
		block->data_reg = sch311x_gpio_blocks[i].data_reg;
		block->runtime_reg = pdata->runtime_reg;

		err = gpiochip_add_data(&block->chip, block);
		if (err < 0) {
			dev_err(&pdev->dev,
				"Could not register gpiochip, %d\n", err);
			goto exit_err;
		}
		dev_info(&pdev->dev,
			 "SMSC SCH311x GPIO block %d registered.\n", i);
	}

	return 0;

exit_err:
	/* release already registered chips */
	for (--i; i >= 0; i--)
		gpiochip_remove(&priv->blocks[i].chip);
	return err;
}