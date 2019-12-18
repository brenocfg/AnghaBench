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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct i2c_demux_pinctrl_priv {int num_chan; TYPE_1__* chan; } ;
struct TYPE_2__ {int /*<<< orphan*/  chgset; int /*<<< orphan*/  parent_np; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_attr_available_masters ; 
 int /*<<< orphan*/  dev_attr_current_master ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_demux_deactivate_master (struct i2c_demux_pinctrl_priv*) ; 
 int /*<<< orphan*/  of_changeset_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ ) ; 
 struct i2c_demux_pinctrl_priv* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int i2c_demux_pinctrl_remove(struct platform_device *pdev)
{
	struct i2c_demux_pinctrl_priv *priv = platform_get_drvdata(pdev);
	int i;

	device_remove_file(&pdev->dev, &dev_attr_current_master);
	device_remove_file(&pdev->dev, &dev_attr_available_masters);

	i2c_demux_deactivate_master(priv);

	for (i = 0; i < priv->num_chan; i++) {
		of_node_put(priv->chan[i].parent_np);
		of_changeset_destroy(&priv->chan[i].chgset);
	}

	return 0;
}