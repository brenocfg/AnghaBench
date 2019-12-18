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
typedef  int /*<<< orphan*/  u8 ;
struct mac_driver {int /*<<< orphan*/  dev; } ;
typedef  enum hnae_loop { ____Placeholder_hnae_loop } hnae_loop ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GMAC_LOOP_REG ; 
 int /*<<< orphan*/  GMAC_LP_REG_CF2MI_LP_EN_B ; 
#define  MAC_INTERNALLOOP_MAC 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dsaf_set_dev_bit (struct mac_driver*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hns_gmac_config_loopback(void *mac_drv, enum hnae_loop loop_mode,
				    u8 enable)
{
	struct mac_driver *drv = (struct mac_driver *)mac_drv;

	switch (loop_mode) {
	case MAC_INTERNALLOOP_MAC:
		dsaf_set_dev_bit(drv, GMAC_LOOP_REG, GMAC_LP_REG_CF2MI_LP_EN_B,
				 !!enable);
		break;
	default:
		dev_err(drv->dev, "loop_mode error\n");
		return -EINVAL;
	}

	return 0;
}