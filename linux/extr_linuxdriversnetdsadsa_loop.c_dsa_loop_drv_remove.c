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
struct mdio_device {int /*<<< orphan*/  dev; } ;
struct dsa_switch {struct dsa_loop_priv* priv; } ;
struct dsa_loop_priv {int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 struct dsa_switch* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsa_unregister_switch (struct dsa_switch*) ; 

__attribute__((used)) static void dsa_loop_drv_remove(struct mdio_device *mdiodev)
{
	struct dsa_switch *ds = dev_get_drvdata(&mdiodev->dev);
	struct dsa_loop_priv *ps = ds->priv;

	dsa_unregister_switch(ds);
	dev_put(ps->netdev);
}