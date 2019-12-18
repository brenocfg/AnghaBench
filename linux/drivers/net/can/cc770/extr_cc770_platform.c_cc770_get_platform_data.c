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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int freq; } ;
struct TYPE_4__ {TYPE_1__ clock; } ;
struct cc770_priv {int cpu_interface; int /*<<< orphan*/  bus_config; int /*<<< orphan*/  clkout; TYPE_2__ can; } ;
struct cc770_platform_data {int osc_freq; int cir; int /*<<< orphan*/  bcr; int /*<<< orphan*/  cor; } ;

/* Variables and functions */
 int CPUIF_DSC ; 
 struct cc770_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cc770_get_platform_data(struct platform_device *pdev,
				   struct cc770_priv *priv)
{

	struct cc770_platform_data *pdata = dev_get_platdata(&pdev->dev);

	priv->can.clock.freq = pdata->osc_freq;
	if (priv->cpu_interface & CPUIF_DSC)
		priv->can.clock.freq /= 2;
	priv->clkout = pdata->cor;
	priv->bus_config = pdata->bcr;
	priv->cpu_interface = pdata->cir;

	return 0;
}