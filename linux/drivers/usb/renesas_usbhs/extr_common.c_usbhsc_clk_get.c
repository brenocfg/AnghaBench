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
struct usbhs_priv {int /*<<< orphan*/ ** clks; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_of_node (struct device*) ; 
 void* of_clk_get (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usbhsc_is_multi_clks (struct usbhs_priv*) ; 

__attribute__((used)) static int usbhsc_clk_get(struct device *dev, struct usbhs_priv *priv)
{
	if (!usbhsc_is_multi_clks(priv))
		return 0;

	/* The first clock should exist */
	priv->clks[0] = of_clk_get(dev_of_node(dev), 0);
	if (IS_ERR(priv->clks[0]))
		return PTR_ERR(priv->clks[0]);

	/*
	 * To backward compatibility with old DT, this driver checks the return
	 * value if it's -ENOENT or not.
	 */
	priv->clks[1] = of_clk_get(dev_of_node(dev), 1);
	if (PTR_ERR(priv->clks[1]) == -ENOENT)
		priv->clks[1] = NULL;
	else if (IS_ERR(priv->clks[1]))
		return PTR_ERR(priv->clks[1]);

	return 0;
}