#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct regmap {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct mxs_phy {TYPE_1__ phy; struct regmap* regmap_anatop; } ;
typedef  enum usb_charger_type { ____Placeholder_usb_charger_type } usb_charger_type ;

/* Variables and functions */
 int ANADIG_USB1_CHRG_DETECT_CHK_CHRG_B ; 
 int ANADIG_USB1_CHRG_DETECT_CHK_CONTACT ; 
 int /*<<< orphan*/  ANADIG_USB1_CHRG_DETECT_CLR ; 
 int ANADIG_USB1_CHRG_DETECT_EN_B ; 
 int /*<<< orphan*/  ANADIG_USB1_CHRG_DETECT_SET ; 
 int /*<<< orphan*/  ANADIG_USB1_CHRG_DET_STAT ; 
 int ANADIG_USB1_CHRG_DET_STAT_CHRG_DETECTED ; 
 int SDP_TYPE ; 
 int UNKNOWN_TYPE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  regmap_read (struct regmap*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static enum usb_charger_type mxs_charger_primary_detection(struct mxs_phy *x)
{
	struct regmap *regmap = x->regmap_anatop;
	enum usb_charger_type chgr_type = UNKNOWN_TYPE;
	u32 val;

	/*
	 * - Do check whether a charger is connected to the USB port
	 * - Do not Check whether the USB plug has been in contact with
	 *   each other
	 */
	regmap_write(regmap, ANADIG_USB1_CHRG_DETECT_CLR,
			ANADIG_USB1_CHRG_DETECT_CHK_CONTACT |
			ANADIG_USB1_CHRG_DETECT_CHK_CHRG_B);

	msleep(100);

	/* Check if it is a charger */
	regmap_read(regmap, ANADIG_USB1_CHRG_DET_STAT, &val);
	if (!(val & ANADIG_USB1_CHRG_DET_STAT_CHRG_DETECTED)) {
		chgr_type = SDP_TYPE;
		dev_dbg(x->phy.dev, "It is a standard downstream port\n");
	}

	/* Disable charger detector */
	regmap_write(regmap, ANADIG_USB1_CHRG_DETECT_SET,
			ANADIG_USB1_CHRG_DETECT_EN_B |
			ANADIG_USB1_CHRG_DETECT_CHK_CHRG_B);

	return chgr_type;
}