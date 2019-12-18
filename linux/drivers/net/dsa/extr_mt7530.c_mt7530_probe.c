#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct mt7530_priv {unsigned int id; TYPE_2__* ds; int /*<<< orphan*/  reg_mutex; TYPE_1__* dev; int /*<<< orphan*/  bus; void* reset; scalar_t__ mcm; void* io_pwr; void* core_pwr; void* rstc; } ;
struct TYPE_12__ {struct device_node* of_node; } ;
struct mdio_device {TYPE_1__ dev; int /*<<< orphan*/  bus; } ;
struct device_node {int dummy; } ;
struct TYPE_13__ {int /*<<< orphan*/ * ops; struct mt7530_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSA_MAX_PORTS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 unsigned int ID_MT7530 ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_1__*,struct mt7530_priv*) ; 
 void* devm_gpiod_get_optional (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 struct mt7530_priv* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 void* devm_regulator_get (TYPE_1__*,char*) ; 
 void* devm_reset_control_get (TYPE_1__*,char*) ; 
 int dsa_register_switch (TYPE_2__*) ; 
 TYPE_2__* dsa_switch_alloc (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt7530_switch_ops ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 scalar_t__ of_device_get_match_data (TYPE_1__*) ; 
 scalar_t__ of_property_read_bool (struct device_node*,char*) ; 

__attribute__((used)) static int
mt7530_probe(struct mdio_device *mdiodev)
{
	struct mt7530_priv *priv;
	struct device_node *dn;

	dn = mdiodev->dev.of_node;

	priv = devm_kzalloc(&mdiodev->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->ds = dsa_switch_alloc(&mdiodev->dev, DSA_MAX_PORTS);
	if (!priv->ds)
		return -ENOMEM;

	/* Use medatek,mcm property to distinguish hardware type that would
	 * casues a little bit differences on power-on sequence.
	 */
	priv->mcm = of_property_read_bool(dn, "mediatek,mcm");
	if (priv->mcm) {
		dev_info(&mdiodev->dev, "MT7530 adapts as multi-chip module\n");

		priv->rstc = devm_reset_control_get(&mdiodev->dev, "mcm");
		if (IS_ERR(priv->rstc)) {
			dev_err(&mdiodev->dev, "Couldn't get our reset line\n");
			return PTR_ERR(priv->rstc);
		}
	}

	/* Get the hardware identifier from the devicetree node.
	 * We will need it for some of the clock and regulator setup.
	 */
	priv->id = (unsigned int)(unsigned long)
		of_device_get_match_data(&mdiodev->dev);

	if (priv->id == ID_MT7530) {
		priv->core_pwr = devm_regulator_get(&mdiodev->dev, "core");
		if (IS_ERR(priv->core_pwr))
			return PTR_ERR(priv->core_pwr);

		priv->io_pwr = devm_regulator_get(&mdiodev->dev, "io");
		if (IS_ERR(priv->io_pwr))
			return PTR_ERR(priv->io_pwr);
	}

	/* Not MCM that indicates switch works as the remote standalone
	 * integrated circuit so the GPIO pin would be used to complete
	 * the reset, otherwise memory-mapped register accessing used
	 * through syscon provides in the case of MCM.
	 */
	if (!priv->mcm) {
		priv->reset = devm_gpiod_get_optional(&mdiodev->dev, "reset",
						      GPIOD_OUT_LOW);
		if (IS_ERR(priv->reset)) {
			dev_err(&mdiodev->dev, "Couldn't get our reset line\n");
			return PTR_ERR(priv->reset);
		}
	}

	priv->bus = mdiodev->bus;
	priv->dev = &mdiodev->dev;
	priv->ds->priv = priv;
	priv->ds->ops = &mt7530_switch_ops;
	mutex_init(&priv->reg_mutex);
	dev_set_drvdata(&mdiodev->dev, priv);

	return dsa_register_switch(priv->ds);
}