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

/* Variables and functions */
 int ANADIG_USB1_CHRG_DETECT_CHK_CHRG_B ; 
 int ANADIG_USB1_CHRG_DETECT_CHK_CONTACT ; 
 int /*<<< orphan*/  ANADIG_USB1_CHRG_DETECT_CLR ; 
 int ANADIG_USB1_CHRG_DETECT_EN_B ; 
 int /*<<< orphan*/  ANADIG_USB1_CHRG_DETECT_SET ; 
 int /*<<< orphan*/  ANADIG_USB1_CHRG_DET_STAT ; 
 int ANADIG_USB1_CHRG_DET_STAT_PLUG_CONTACT ; 
 int /*<<< orphan*/  ANADIG_USB1_VBUS_DET_STAT ; 
 int ANADIG_USB1_VBUS_DET_STAT_VBUS_VALID ; 
 int EINVAL ; 
 int ENXIO ; 
 int MXS_USB_CHARGER_DATA_CONTACT_TIMEOUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  regmap_read (struct regmap*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int mxs_charger_data_contact_detect(struct mxs_phy *x)
{
	struct regmap *regmap = x->regmap_anatop;
	int i, stable_contact_count = 0;
	u32 val;

	/* Check if vbus is valid */
	regmap_read(regmap, ANADIG_USB1_VBUS_DET_STAT, &val);
	if (!(val & ANADIG_USB1_VBUS_DET_STAT_VBUS_VALID)) {
		dev_err(x->phy.dev, "vbus is not valid\n");
		return -EINVAL;
	}

	/* Enable charger detector */
	regmap_write(regmap, ANADIG_USB1_CHRG_DETECT_CLR,
				ANADIG_USB1_CHRG_DETECT_EN_B);
	/*
	 * - Do not check whether a charger is connected to the USB port
	 * - Check whether the USB plug has been in contact with each other
	 */
	regmap_write(regmap, ANADIG_USB1_CHRG_DETECT_SET,
			ANADIG_USB1_CHRG_DETECT_CHK_CONTACT |
			ANADIG_USB1_CHRG_DETECT_CHK_CHRG_B);

	/* Check if plug is connected */
	for (i = 0; i < MXS_USB_CHARGER_DATA_CONTACT_TIMEOUT; i++) {
		regmap_read(regmap, ANADIG_USB1_CHRG_DET_STAT, &val);
		if (val & ANADIG_USB1_CHRG_DET_STAT_PLUG_CONTACT) {
			stable_contact_count++;
			if (stable_contact_count > 5)
				/* Data pin makes contact */
				break;
			else
				usleep_range(5000, 10000);
		} else {
			stable_contact_count = 0;
			usleep_range(5000, 6000);
		}
	}

	if (i == MXS_USB_CHARGER_DATA_CONTACT_TIMEOUT) {
		dev_err(x->phy.dev,
			"Data pin can't make good contact.\n");
		/* Disable charger detector */
		regmap_write(regmap, ANADIG_USB1_CHRG_DETECT_SET,
				ANADIG_USB1_CHRG_DETECT_EN_B |
				ANADIG_USB1_CHRG_DETECT_CHK_CHRG_B);
		return -ENXIO;
	}

	return 0;
}