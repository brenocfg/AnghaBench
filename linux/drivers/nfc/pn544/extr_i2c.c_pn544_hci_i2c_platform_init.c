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
struct pn544_i2c_phy {int en_polarity; int /*<<< orphan*/  gpiod_en; TYPE_1__* i2c_dev; int /*<<< orphan*/  gpiod_fw; } ;
typedef  int /*<<< orphan*/  rset_cmd ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 int i2c_master_send (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  nfc_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  nfc_info (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void pn544_hci_i2c_platform_init(struct pn544_i2c_phy *phy)
{
	int polarity, retry, ret;
	char rset_cmd[] = { 0x05, 0xF9, 0x04, 0x00, 0xC3, 0xE5 };
	int count = sizeof(rset_cmd);

	nfc_info(&phy->i2c_dev->dev, "Detecting nfc_en polarity\n");

	/* Disable fw download */
	gpiod_set_value_cansleep(phy->gpiod_fw, 0);

	for (polarity = 0; polarity < 2; polarity++) {
		phy->en_polarity = polarity;
		retry = 3;
		while (retry--) {
			/* power off */
			gpiod_set_value_cansleep(phy->gpiod_en, !phy->en_polarity);
			usleep_range(10000, 15000);

			/* power on */
			gpiod_set_value_cansleep(phy->gpiod_en, phy->en_polarity);
			usleep_range(10000, 15000);

			/* send reset */
			dev_dbg(&phy->i2c_dev->dev, "Sending reset cmd\n");
			ret = i2c_master_send(phy->i2c_dev, rset_cmd, count);
			if (ret == count) {
				nfc_info(&phy->i2c_dev->dev,
					 "nfc_en polarity : active %s\n",
					 (polarity == 0 ? "low" : "high"));
				goto out;
			}
		}
	}

	nfc_err(&phy->i2c_dev->dev,
		"Could not detect nfc_en polarity, fallback to active high\n");

out:
	gpiod_set_value_cansleep(phy->gpiod_en, !phy->en_polarity);
}