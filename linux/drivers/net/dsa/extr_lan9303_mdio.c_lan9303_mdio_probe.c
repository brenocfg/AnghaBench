#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  of_node; } ;
struct mdio_device {TYPE_2__ dev; } ;
struct TYPE_7__ {int /*<<< orphan*/ * ops; TYPE_2__* dev; int /*<<< orphan*/  regmap; } ;
struct lan9303_mdio {TYPE_1__ chip; struct mdio_device* device; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  dev_info (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_2__*,struct lan9303_mdio*) ; 
 struct lan9303_mdio* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init (TYPE_2__*,int /*<<< orphan*/ *,struct lan9303_mdio*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lan9303_mdio_phy_ops ; 
 int /*<<< orphan*/  lan9303_mdio_regmap_config ; 
 int lan9303_probe (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lan9303_mdio_probe(struct mdio_device *mdiodev)
{
	struct lan9303_mdio *sw_dev;
	int ret;

	sw_dev = devm_kzalloc(&mdiodev->dev, sizeof(struct lan9303_mdio),
			      GFP_KERNEL);
	if (!sw_dev)
		return -ENOMEM;

	sw_dev->chip.regmap = devm_regmap_init(&mdiodev->dev, NULL, sw_dev,
					       &lan9303_mdio_regmap_config);
	if (IS_ERR(sw_dev->chip.regmap)) {
		ret = PTR_ERR(sw_dev->chip.regmap);
		dev_err(&mdiodev->dev, "regmap init failed: %d\n", ret);
		return ret;
	}

	/* link forward and backward */
	sw_dev->device = mdiodev;
	dev_set_drvdata(&mdiodev->dev, sw_dev);
	sw_dev->chip.dev = &mdiodev->dev;

	sw_dev->chip.ops = &lan9303_mdio_phy_ops;

	ret = lan9303_probe(&sw_dev->chip, mdiodev->dev.of_node);
	if (ret != 0)
		return ret;

	dev_info(&mdiodev->dev, "LAN9303 MDIO driver loaded successfully\n");

	return 0;
}