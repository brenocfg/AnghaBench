#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int dummy; } ;
struct bcm_sf2_priv {TYPE_1__* dev; scalar_t__ wol_ports_mask; } ;
struct TYPE_2__ {int /*<<< orphan*/  ds; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcm_sf2_cfp_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm_sf2_intr_disable (struct bcm_sf2_priv*) ; 
 int /*<<< orphan*/  bcm_sf2_mdio_unregister (struct bcm_sf2_priv*) ; 
 int /*<<< orphan*/  dsa_unregister_switch (int /*<<< orphan*/ ) ; 
 struct bcm_sf2_priv* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int bcm_sf2_sw_remove(struct platform_device *pdev)
{
	struct bcm_sf2_priv *priv = platform_get_drvdata(pdev);

	priv->wol_ports_mask = 0;
	/* Disable interrupts */
	bcm_sf2_intr_disable(priv);
	dsa_unregister_switch(priv->dev->ds);
	bcm_sf2_cfp_exit(priv->dev->ds);
	bcm_sf2_mdio_unregister(priv);

	return 0;
}