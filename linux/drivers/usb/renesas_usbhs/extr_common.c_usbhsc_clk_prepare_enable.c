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
struct usbhs_priv {int /*<<< orphan*/ * clks; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbhsc_is_multi_clks (struct usbhs_priv*) ; 

__attribute__((used)) static int usbhsc_clk_prepare_enable(struct usbhs_priv *priv)
{
	int i, ret;

	if (!usbhsc_is_multi_clks(priv))
		return 0;

	for (i = 0; i < ARRAY_SIZE(priv->clks); i++) {
		ret = clk_prepare_enable(priv->clks[i]);
		if (ret) {
			while (--i >= 0)
				clk_disable_unprepare(priv->clks[i]);
			return ret;
		}
	}

	return ret;
}