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
typedef  int u8 ;
struct bq24190_dev_info {int /*<<< orphan*/  dev; int /*<<< orphan*/  edev; } ;

/* Variables and functions */
 int BQ24190_REG_SS_VBUS_STAT_MASK ; 
 int /*<<< orphan*/  EXTCON_USB ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int) ; 
 int extcon_set_state_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int bq24190_configure_usb_otg(struct bq24190_dev_info *bdi, u8 ss_reg)
{
	bool otg_enabled;
	int ret;

	otg_enabled = !!(ss_reg & BQ24190_REG_SS_VBUS_STAT_MASK);
	ret = extcon_set_state_sync(bdi->edev, EXTCON_USB, otg_enabled);
	if (ret < 0)
		dev_err(bdi->dev, "Can't set extcon state to %d: %d\n",
			otg_enabled, ret);

	return ret;
}