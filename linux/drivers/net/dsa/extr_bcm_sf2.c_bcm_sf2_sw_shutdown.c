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
struct platform_device {int dummy; } ;
struct TYPE_3__ {int num_gphy; } ;
struct bcm_sf2_priv {TYPE_2__* dev; TYPE_1__ hw_params; } ;
struct TYPE_4__ {int /*<<< orphan*/  ds; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcm_sf2_gphy_enable_set (int /*<<< orphan*/ ,int) ; 
 struct bcm_sf2_priv* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static void bcm_sf2_sw_shutdown(struct platform_device *pdev)
{
	struct bcm_sf2_priv *priv = platform_get_drvdata(pdev);

	/* For a kernel about to be kexec'd we want to keep the GPHY on for a
	 * successful MDIO bus scan to occur. If we did turn off the GPHY
	 * before (e.g: port_disable), this will also power it back on.
	 *
	 * Do not rely on kexec_in_progress, just power the PHY on.
	 */
	if (priv->hw_params.num_gphy == 1)
		bcm_sf2_gphy_enable_set(priv->dev->ds, true);
}