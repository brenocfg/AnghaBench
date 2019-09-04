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
struct lmac {int lmac_type; int lane_to_sds; int lmacid; } ;
struct bgx {int dummy; } ;

/* Variables and functions */
#define  BGX_MODE_QSGMII 134 
#define  BGX_MODE_RGMII 133 
#define  BGX_MODE_RXAUI 132 
#define  BGX_MODE_SGMII 131 
#define  BGX_MODE_XAUI 130 
#define  BGX_MODE_XFI 129 
#define  BGX_MODE_XLAUI 128 
 int bgx_get_lane2sds_cfg (struct bgx*,struct lmac*) ; 

__attribute__((used)) static void lmac_set_lane2sds(struct bgx *bgx, struct lmac *lmac)
{
	switch (lmac->lmac_type) {
	case BGX_MODE_SGMII:
	case BGX_MODE_XFI:
		lmac->lane_to_sds = lmac->lmacid;
		break;
	case BGX_MODE_XAUI:
	case BGX_MODE_XLAUI:
	case BGX_MODE_RGMII:
		lmac->lane_to_sds = 0xE4;
		break;
	case BGX_MODE_RXAUI:
		lmac->lane_to_sds = (lmac->lmacid) ? 0xE : 0x4;
		break;
	case BGX_MODE_QSGMII:
		/* There is no way to determine if DLM0/2 is QSGMII or
		 * DLM1/3 is configured to QSGMII as bootloader will
		 * configure all LMACs, so take whatever is configured
		 * by low level firmware.
		 */
		lmac->lane_to_sds = bgx_get_lane2sds_cfg(bgx, lmac);
		break;
	default:
		lmac->lane_to_sds = 0;
		break;
	}
}