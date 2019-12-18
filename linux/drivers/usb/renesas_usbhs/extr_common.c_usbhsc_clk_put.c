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
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbhsc_is_multi_clks (struct usbhs_priv*) ; 

__attribute__((used)) static void usbhsc_clk_put(struct usbhs_priv *priv)
{
	int i;

	if (!usbhsc_is_multi_clks(priv))
		return;

	for (i = 0; i < ARRAY_SIZE(priv->clks); i++)
		clk_put(priv->clks[i]);
}