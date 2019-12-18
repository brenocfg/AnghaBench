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
struct TYPE_2__ {int /*<<< orphan*/  phy; } ;
struct wl18xx_priv {TYPE_1__ conf; } ;
struct wl18xx_mac_and_phy_params {int dummy; } ;
struct wl1271 {int /*<<< orphan*/ * ptable; struct wl18xx_priv* priv; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t PART_PHY_INIT ; 
 int /*<<< orphan*/  WL18XX_PHY_INIT_MEM_ADDR ; 
 int /*<<< orphan*/  kfree (struct wl18xx_mac_and_phy_params*) ; 
 struct wl18xx_mac_and_phy_params* kmemdup (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int wlcore_set_partition (struct wl1271*,int /*<<< orphan*/ *) ; 
 int wlcore_write (struct wl1271*,int /*<<< orphan*/ ,struct wl18xx_mac_and_phy_params*,int,int) ; 

__attribute__((used)) static int wl18xx_set_mac_and_phy(struct wl1271 *wl)
{
	struct wl18xx_priv *priv = wl->priv;
	struct wl18xx_mac_and_phy_params *params;
	int ret;

	params = kmemdup(&priv->conf.phy, sizeof(*params), GFP_KERNEL);
	if (!params) {
		ret = -ENOMEM;
		goto out;
	}

	ret = wlcore_set_partition(wl, &wl->ptable[PART_PHY_INIT]);
	if (ret < 0)
		goto out;

	ret = wlcore_write(wl, WL18XX_PHY_INIT_MEM_ADDR, params,
			   sizeof(*params), false);

out:
	kfree(params);
	return ret;
}