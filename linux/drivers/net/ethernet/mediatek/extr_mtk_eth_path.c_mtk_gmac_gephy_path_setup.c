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
struct mtk_eth {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int MTK_ETH_PATH_GMAC2_GEPHY ; 
 int mtk_eth_mux_setup (struct mtk_eth*,int) ; 

int mtk_gmac_gephy_path_setup(struct mtk_eth *eth, int mac_id)
{
	int err, path = 0;

	if (mac_id == 1)
		path = MTK_ETH_PATH_GMAC2_GEPHY;

	if (!path)
		return -EINVAL;

	/* Setup proper MUXes along the path */
	err = mtk_eth_mux_setup(eth, path);
	if (err)
		return err;

	return 0;
}