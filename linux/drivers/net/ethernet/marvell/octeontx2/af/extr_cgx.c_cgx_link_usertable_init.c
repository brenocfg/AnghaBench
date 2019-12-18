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
 size_t CGX_LINK_100G ; 
 size_t CGX_LINK_100M ; 
 size_t CGX_LINK_10G ; 
 size_t CGX_LINK_10M ; 
 size_t CGX_LINK_1G ; 
 size_t CGX_LINK_20G ; 
 size_t CGX_LINK_25G ; 
 size_t CGX_LINK_2HG ; 
 size_t CGX_LINK_40G ; 
 size_t CGX_LINK_50G ; 
 size_t CGX_LINK_5G ; 
 size_t CGX_LINK_NONE ; 
 size_t LMAC_MODE_100G_R ; 
 size_t LMAC_MODE_10G_R ; 
 size_t LMAC_MODE_25G_R ; 
 size_t LMAC_MODE_40G_R ; 
 size_t LMAC_MODE_50G_R ; 
 size_t LMAC_MODE_QSGMII ; 
 size_t LMAC_MODE_RXAUI ; 
 size_t LMAC_MODE_SGMII ; 
 size_t LMAC_MODE_USXGMII ; 
 size_t LMAC_MODE_XAUI ; 
 char** cgx_lmactype_string ; 
 int* cgx_speed_mbps ; 

__attribute__((used)) static inline void cgx_link_usertable_init(void)
{
	cgx_speed_mbps[CGX_LINK_NONE] = 0;
	cgx_speed_mbps[CGX_LINK_10M] = 10;
	cgx_speed_mbps[CGX_LINK_100M] = 100;
	cgx_speed_mbps[CGX_LINK_1G] = 1000;
	cgx_speed_mbps[CGX_LINK_2HG] = 2500;
	cgx_speed_mbps[CGX_LINK_5G] = 5000;
	cgx_speed_mbps[CGX_LINK_10G] = 10000;
	cgx_speed_mbps[CGX_LINK_20G] = 20000;
	cgx_speed_mbps[CGX_LINK_25G] = 25000;
	cgx_speed_mbps[CGX_LINK_40G] = 40000;
	cgx_speed_mbps[CGX_LINK_50G] = 50000;
	cgx_speed_mbps[CGX_LINK_100G] = 100000;

	cgx_lmactype_string[LMAC_MODE_SGMII] = "SGMII";
	cgx_lmactype_string[LMAC_MODE_XAUI] = "XAUI";
	cgx_lmactype_string[LMAC_MODE_RXAUI] = "RXAUI";
	cgx_lmactype_string[LMAC_MODE_10G_R] = "10G_R";
	cgx_lmactype_string[LMAC_MODE_40G_R] = "40G_R";
	cgx_lmactype_string[LMAC_MODE_QSGMII] = "QSGMII";
	cgx_lmactype_string[LMAC_MODE_25G_R] = "25G_R";
	cgx_lmactype_string[LMAC_MODE_50G_R] = "50G_R";
	cgx_lmactype_string[LMAC_MODE_100G_R] = "100G_R";
	cgx_lmactype_string[LMAC_MODE_USXGMII] = "USXGMII";
}