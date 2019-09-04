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
typedef  int /*<<< orphan*/  u32 ;
struct mac_driver {int /*<<< orphan*/  mac_id; int /*<<< orphan*/  dev; } ;
typedef  enum mac_speed { ____Placeholder_mac_speed } mac_speed ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GMAC_DUPLEX_TYPE_B ; 
 int /*<<< orphan*/  GMAC_DUPLEX_TYPE_REG ; 
 int /*<<< orphan*/  GMAC_PORT_MODE_M ; 
 int /*<<< orphan*/  GMAC_PORT_MODE_REG ; 
 int /*<<< orphan*/  GMAC_PORT_MODE_S ; 
#define  MAC_SPEED_10 130 
#define  MAC_SPEED_100 129 
#define  MAC_SPEED_1000 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsaf_set_dev_bit (struct mac_driver*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dsaf_set_dev_field (struct mac_driver*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hns_gmac_adjust_link(void *mac_drv, enum mac_speed speed,
				u32 full_duplex)
{
	struct mac_driver *drv = (struct mac_driver *)mac_drv;

	dsaf_set_dev_bit(drv, GMAC_DUPLEX_TYPE_REG,
			 GMAC_DUPLEX_TYPE_B, !!full_duplex);

	switch (speed) {
	case MAC_SPEED_10:
		dsaf_set_dev_field(
			drv, GMAC_PORT_MODE_REG,
			GMAC_PORT_MODE_M, GMAC_PORT_MODE_S, 0x6);
		break;
	case MAC_SPEED_100:
		dsaf_set_dev_field(
			drv, GMAC_PORT_MODE_REG,
			GMAC_PORT_MODE_M, GMAC_PORT_MODE_S, 0x7);
		break;
	case MAC_SPEED_1000:
		dsaf_set_dev_field(
			drv, GMAC_PORT_MODE_REG,
			GMAC_PORT_MODE_M, GMAC_PORT_MODE_S, 0x8);
		break;
	default:
		dev_err(drv->dev,
			"hns_gmac_adjust_link fail, speed%d mac%d\n",
			speed, drv->mac_id);
		return -EINVAL;
	}

	return 0;
}