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
typedef  int u8 ;
typedef  int u32 ;
struct m88rs6000t_dev {int frequency_khz; TYPE_1__* client; int /*<<< orphan*/  regmap; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int,unsigned int*) ; 
 int regmap_write (int /*<<< orphan*/ ,int,unsigned int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int m88rs6000t_set_pll_freq(struct m88rs6000t_dev *dev,
			u32 tuner_freq_MHz)
{
	u32 fcry_KHz, ulNDiv1, ulNDiv2, ulNDiv;
	u8 refDiv, ucLoDiv1, ucLomod1, ucLoDiv2, ucLomod2, ucLoDiv, ucLomod;
	u8 reg27, reg29, reg42, reg42buf;
	unsigned int utmp;
	int ret;

	fcry_KHz = 27000; /* in kHz */
	refDiv = 27;

	ret = regmap_write(dev->regmap, 0x36, (refDiv - 8));
	if (ret)
		goto err;
	ret = regmap_write(dev->regmap, 0x31, 0x00);
	if (ret)
		goto err;
	ret = regmap_write(dev->regmap, 0x2c, 0x02);
	if (ret)
		goto err;

	if (tuner_freq_MHz >= 1550) {
		ucLoDiv1 = 2;
		ucLomod1 = 0;
		ucLoDiv2 = 2;
		ucLomod2 = 0;
	} else if (tuner_freq_MHz >= 1380) {
		ucLoDiv1 = 3;
		ucLomod1 = 16;
		ucLoDiv2 = 2;
		ucLomod2 = 0;
	} else if (tuner_freq_MHz >= 1070) {
		ucLoDiv1 = 3;
		ucLomod1 = 16;
		ucLoDiv2 = 3;
		ucLomod2 = 16;
	} else if (tuner_freq_MHz >= 1000) {
		ucLoDiv1 = 3;
		ucLomod1 = 16;
		ucLoDiv2 = 4;
		ucLomod2 = 64;
	} else if (tuner_freq_MHz >= 775) {
		ucLoDiv1 = 4;
		ucLomod1 = 64;
		ucLoDiv2 = 4;
		ucLomod2 = 64;
	} else if (tuner_freq_MHz >= 700) {
		ucLoDiv1 = 6;
		ucLomod1 = 48;
		ucLoDiv2 = 4;
		ucLomod2 = 64;
	} else if (tuner_freq_MHz >= 520) {
		ucLoDiv1 = 6;
		ucLomod1 = 48;
		ucLoDiv2 = 6;
		ucLomod2 = 48;
	} else {
		ucLoDiv1 = 8;
		ucLomod1 = 96;
		ucLoDiv2 = 8;
		ucLomod2 = 96;
	}

	ulNDiv1 = ((tuner_freq_MHz * ucLoDiv1 * 1000) * refDiv
			/ fcry_KHz - 1024) / 2;
	ulNDiv2 = ((tuner_freq_MHz * ucLoDiv2 * 1000) * refDiv
			/ fcry_KHz - 1024) / 2;

	reg27 = (((ulNDiv1 >> 8) & 0x0F) + ucLomod1) & 0x7F;
	ret = regmap_write(dev->regmap, 0x27, reg27);
	if (ret)
		goto err;
	ret = regmap_write(dev->regmap, 0x28, (u8)(ulNDiv1 & 0xFF));
	if (ret)
		goto err;
	reg29 = (((ulNDiv2 >> 8) & 0x0F) + ucLomod2) & 0x7f;
	ret = regmap_write(dev->regmap, 0x29, reg29);
	if (ret)
		goto err;
	ret = regmap_write(dev->regmap, 0x2a, (u8)(ulNDiv2 & 0xFF));
	if (ret)
		goto err;
	ret = regmap_write(dev->regmap, 0x2F, 0xf5);
	if (ret)
		goto err;
	ret = regmap_write(dev->regmap, 0x30, 0x05);
	if (ret)
		goto err;
	ret = regmap_write(dev->regmap, 0x08, 0x1f);
	if (ret)
		goto err;
	ret = regmap_write(dev->regmap, 0x08, 0x3f);
	if (ret)
		goto err;
	ret = regmap_write(dev->regmap, 0x09, 0x20);
	if (ret)
		goto err;
	ret = regmap_write(dev->regmap, 0x09, 0x00);
	if (ret)
		goto err;
	ret = regmap_write(dev->regmap, 0x3e, 0x11);
	if (ret)
		goto err;
	ret = regmap_write(dev->regmap, 0x08, 0x2f);
	if (ret)
		goto err;
	ret = regmap_write(dev->regmap, 0x08, 0x3f);
	if (ret)
		goto err;
	ret = regmap_write(dev->regmap, 0x09, 0x10);
	if (ret)
		goto err;
	ret = regmap_write(dev->regmap, 0x09, 0x00);
	if (ret)
		goto err;
	usleep_range(2000, 50000);

	ret = regmap_read(dev->regmap, 0x42, &utmp);
	if (ret)
		goto err;
	reg42 = utmp;

	ret = regmap_write(dev->regmap, 0x3e, 0x10);
	if (ret)
		goto err;
	ret = regmap_write(dev->regmap, 0x08, 0x2f);
	if (ret)
		goto err;
	ret = regmap_write(dev->regmap, 0x08, 0x3f);
	if (ret)
		goto err;
	ret = regmap_write(dev->regmap, 0x09, 0x10);
	if (ret)
		goto err;
	ret = regmap_write(dev->regmap, 0x09, 0x00);
	if (ret)
		goto err;
	usleep_range(2000, 50000);

	ret = regmap_read(dev->regmap, 0x42, &utmp);
	if (ret)
		goto err;
	reg42buf = utmp;
	if (reg42buf < reg42) {
		ret = regmap_write(dev->regmap, 0x3e, 0x11);
		if (ret)
			goto err;
	}
	usleep_range(5000, 50000);

	ret = regmap_read(dev->regmap, 0x2d, &utmp);
	if (ret)
		goto err;
	ret = regmap_write(dev->regmap, 0x2d, utmp);
	if (ret)
		goto err;
	ret = regmap_read(dev->regmap, 0x2e, &utmp);
	if (ret)
		goto err;
	ret = regmap_write(dev->regmap, 0x2e, utmp);
	if (ret)
		goto err;

	ret = regmap_read(dev->regmap, 0x27, &utmp);
	if (ret)
		goto err;
	reg27 = utmp & 0x70;
	ret = regmap_read(dev->regmap, 0x83, &utmp);
	if (ret)
		goto err;
	if (reg27 == (utmp & 0x70)) {
		ucLoDiv	= ucLoDiv1;
		ulNDiv = ulNDiv1;
		ucLomod = ucLomod1 / 16;
	} else {
		ucLoDiv	= ucLoDiv2;
		ulNDiv = ulNDiv2;
		ucLomod = ucLomod2 / 16;
	}

	if ((ucLoDiv == 3) || (ucLoDiv == 6)) {
		refDiv = 18;
		ret = regmap_write(dev->regmap, 0x36, (refDiv - 8));
		if (ret)
			goto err;
		ulNDiv = ((tuner_freq_MHz * ucLoDiv * 1000) * refDiv
				/ fcry_KHz - 1024) / 2;
	}

	reg27 = (0x80 + ((ucLomod << 4) & 0x70)
			+ ((ulNDiv >> 8) & 0x0F)) & 0xFF;
	ret = regmap_write(dev->regmap, 0x27, reg27);
	if (ret)
		goto err;
	ret = regmap_write(dev->regmap, 0x28, (u8)(ulNDiv & 0xFF));
	if (ret)
		goto err;
	ret = regmap_write(dev->regmap, 0x29, 0x80);
	if (ret)
		goto err;
	ret = regmap_write(dev->regmap, 0x31, 0x03);
	if (ret)
		goto err;

	if (ucLoDiv == 3)
		utmp = 0xCE;
	else
		utmp = 0x8A;
	ret = regmap_write(dev->regmap, 0x3b, utmp);
	if (ret)
		goto err;

	dev->frequency_khz = fcry_KHz * (ulNDiv * 2 + 1024) / refDiv / ucLoDiv;

	dev_dbg(&dev->client->dev,
		"actual tune frequency=%d\n", dev->frequency_khz);
err:
	if (ret)
		dev_dbg(&dev->client->dev, "failed=%d\n", ret);
	return ret;
}