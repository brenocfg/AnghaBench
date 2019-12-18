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

/* Variables and functions */
#define  MTK_ETH_PATH_GDM1_ESW 134 
#define  MTK_ETH_PATH_GMAC1_RGMII 133 
#define  MTK_ETH_PATH_GMAC1_SGMII 132 
#define  MTK_ETH_PATH_GMAC1_TRGMII 131 
#define  MTK_ETH_PATH_GMAC2_GEPHY 130 
#define  MTK_ETH_PATH_GMAC2_RGMII 129 
#define  MTK_ETH_PATH_GMAC2_SGMII 128 

__attribute__((used)) static const char *mtk_eth_path_name(int path)
{
	switch (path) {
	case MTK_ETH_PATH_GMAC1_RGMII:
		return "gmac1_rgmii";
	case MTK_ETH_PATH_GMAC1_TRGMII:
		return "gmac1_trgmii";
	case MTK_ETH_PATH_GMAC1_SGMII:
		return "gmac1_sgmii";
	case MTK_ETH_PATH_GMAC2_RGMII:
		return "gmac2_rgmii";
	case MTK_ETH_PATH_GMAC2_SGMII:
		return "gmac2_sgmii";
	case MTK_ETH_PATH_GMAC2_GEPHY:
		return "gmac2_gephy";
	case MTK_ETH_PATH_GDM1_ESW:
		return "gdm1_esw";
	default:
		return "unknown path";
	}
}