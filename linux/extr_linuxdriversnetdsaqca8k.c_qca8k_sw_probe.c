#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct qca8k_priv {TYPE_1__* ds; int /*<<< orphan*/  reg_mutex; int /*<<< orphan*/ * dev; int /*<<< orphan*/  bus; } ;
struct mdio_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  bus; } ;
struct TYPE_3__ {int /*<<< orphan*/ * ops; struct qca8k_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSA_MAX_PORTS ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int QCA8K_ID_QCA8337 ; 
 int QCA8K_MASK_CTRL_ID_M ; 
 int QCA8K_MASK_CTRL_ID_S ; 
 int /*<<< orphan*/  QCA8K_REG_MASK_CTRL ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct qca8k_priv*) ; 
 struct qca8k_priv* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int dsa_register_switch (TYPE_1__*) ; 
 TYPE_1__* dsa_switch_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int qca8k_read (struct qca8k_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qca8k_switch_ops ; 

__attribute__((used)) static int
qca8k_sw_probe(struct mdio_device *mdiodev)
{
	struct qca8k_priv *priv;
	u32 id;

	/* allocate the private data struct so that we can probe the switches
	 * ID register
	 */
	priv = devm_kzalloc(&mdiodev->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->bus = mdiodev->bus;
	priv->dev = &mdiodev->dev;

	/* read the switches ID register */
	id = qca8k_read(priv, QCA8K_REG_MASK_CTRL);
	id >>= QCA8K_MASK_CTRL_ID_S;
	id &= QCA8K_MASK_CTRL_ID_M;
	if (id != QCA8K_ID_QCA8337)
		return -ENODEV;

	priv->ds = dsa_switch_alloc(&mdiodev->dev, DSA_MAX_PORTS);
	if (!priv->ds)
		return -ENOMEM;

	priv->ds->priv = priv;
	priv->ds->ops = &qca8k_switch_ops;
	mutex_init(&priv->reg_mutex);
	dev_set_drvdata(&mdiodev->dev, priv);

	return dsa_register_switch(priv->ds);
}