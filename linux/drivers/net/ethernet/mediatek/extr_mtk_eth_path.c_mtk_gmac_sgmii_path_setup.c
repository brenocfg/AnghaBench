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
 int MTK_ETH_PATH_GMAC1_SGMII ; 
 int MTK_ETH_PATH_GMAC2_SGMII ; 
 int mtk_eth_mux_setup (struct mtk_eth*,int) ; 

int mtk_gmac_sgmii_path_setup(struct mtk_eth *eth, int mac_id)
{
	int err, path;

	path = (mac_id == 0) ?  MTK_ETH_PATH_GMAC1_SGMII :
				MTK_ETH_PATH_GMAC2_SGMII;

	/* Setup proper MUXes along the path */
	err = mtk_eth_mux_setup(eth, path);
	if (err)
		return err;

	return 0;
}