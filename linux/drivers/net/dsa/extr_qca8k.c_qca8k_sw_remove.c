#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct qca8k_priv {int /*<<< orphan*/  ds; } ;
struct mdio_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int QCA8K_NUM_PORTS ; 
 struct qca8k_priv* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsa_unregister_switch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qca8k_port_set_status (struct qca8k_priv*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
qca8k_sw_remove(struct mdio_device *mdiodev)
{
	struct qca8k_priv *priv = dev_get_drvdata(&mdiodev->dev);
	int i;

	for (i = 0; i < QCA8K_NUM_PORTS; i++)
		qca8k_port_set_status(priv, i, 0);

	dsa_unregister_switch(priv->ds);
}