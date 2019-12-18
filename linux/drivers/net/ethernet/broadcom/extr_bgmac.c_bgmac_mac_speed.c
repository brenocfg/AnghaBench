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
typedef  int u32 ;
struct bgmac {int mac_speed; scalar_t__ mac_duplex; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BGMAC_CMDCFG_ES_10 ; 
 int BGMAC_CMDCFG_ES_100 ; 
 int BGMAC_CMDCFG_ES_1000 ; 
 int BGMAC_CMDCFG_ES_2500 ; 
 int BGMAC_CMDCFG_ES_MASK ; 
 int BGMAC_CMDCFG_HD ; 
 scalar_t__ DUPLEX_HALF ; 
#define  SPEED_10 131 
#define  SPEED_100 130 
#define  SPEED_1000 129 
#define  SPEED_2500 128 
 int /*<<< orphan*/  bgmac_cmdcfg_maskset (struct bgmac*,int,int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void bgmac_mac_speed(struct bgmac *bgmac)
{
	u32 mask = ~(BGMAC_CMDCFG_ES_MASK | BGMAC_CMDCFG_HD);
	u32 set = 0;

	switch (bgmac->mac_speed) {
	case SPEED_10:
		set |= BGMAC_CMDCFG_ES_10;
		break;
	case SPEED_100:
		set |= BGMAC_CMDCFG_ES_100;
		break;
	case SPEED_1000:
		set |= BGMAC_CMDCFG_ES_1000;
		break;
	case SPEED_2500:
		set |= BGMAC_CMDCFG_ES_2500;
		break;
	default:
		dev_err(bgmac->dev, "Unsupported speed: %d\n",
			bgmac->mac_speed);
	}

	if (bgmac->mac_duplex == DUPLEX_HALF)
		set |= BGMAC_CMDCFG_HD;

	bgmac_cmdcfg_maskset(bgmac, mask, set, true);
}