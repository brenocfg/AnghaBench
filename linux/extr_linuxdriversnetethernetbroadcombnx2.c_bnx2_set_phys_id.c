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
struct net_device {int dummy; } ;
struct bnx2 {int leds_save; } ;
typedef  enum ethtool_phys_id_state { ____Placeholder_ethtool_phys_id_state } ethtool_phys_id_state ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2_EMAC_LED ; 
 int BNX2_EMAC_LED_1000MB_OVERRIDE ; 
 int BNX2_EMAC_LED_100MB_OVERRIDE ; 
 int BNX2_EMAC_LED_10MB_OVERRIDE ; 
 int BNX2_EMAC_LED_OVERRIDE ; 
 int BNX2_EMAC_LED_TRAFFIC ; 
 int BNX2_EMAC_LED_TRAFFIC_OVERRIDE ; 
 int /*<<< orphan*/  BNX2_MISC_CFG ; 
 int BNX2_MISC_CFG_LEDMODE_MAC ; 
 int BNX2_RD (struct bnx2*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BNX2_WR (struct bnx2*,int /*<<< orphan*/ ,int) ; 
#define  ETHTOOL_ID_ACTIVE 131 
#define  ETHTOOL_ID_INACTIVE 130 
#define  ETHTOOL_ID_OFF 129 
#define  ETHTOOL_ID_ON 128 
 struct bnx2* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int
bnx2_set_phys_id(struct net_device *dev, enum ethtool_phys_id_state state)
{
	struct bnx2 *bp = netdev_priv(dev);

	switch (state) {
	case ETHTOOL_ID_ACTIVE:
		bp->leds_save = BNX2_RD(bp, BNX2_MISC_CFG);
		BNX2_WR(bp, BNX2_MISC_CFG, BNX2_MISC_CFG_LEDMODE_MAC);
		return 1;	/* cycle on/off once per second */

	case ETHTOOL_ID_ON:
		BNX2_WR(bp, BNX2_EMAC_LED, BNX2_EMAC_LED_OVERRIDE |
			BNX2_EMAC_LED_1000MB_OVERRIDE |
			BNX2_EMAC_LED_100MB_OVERRIDE |
			BNX2_EMAC_LED_10MB_OVERRIDE |
			BNX2_EMAC_LED_TRAFFIC_OVERRIDE |
			BNX2_EMAC_LED_TRAFFIC);
		break;

	case ETHTOOL_ID_OFF:
		BNX2_WR(bp, BNX2_EMAC_LED, BNX2_EMAC_LED_OVERRIDE);
		break;

	case ETHTOOL_ID_INACTIVE:
		BNX2_WR(bp, BNX2_EMAC_LED, 0);
		BNX2_WR(bp, BNX2_MISC_CFG, bp->leds_save);
		break;
	}

	return 0;
}