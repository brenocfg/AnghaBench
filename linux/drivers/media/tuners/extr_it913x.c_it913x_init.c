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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct it913x_dev {int role; unsigned int clk_mode; int xtal; int fdiv; unsigned int fn_min; int chip_ver; int active; int /*<<< orphan*/  regmap; struct platform_device* pdev; } ;
struct dvb_frontend {struct it913x_dev* tuner_priv; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int const*) ; 
 scalar_t__ TIMEOUT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,unsigned int) ; 
 unsigned long jiffies ; 
 scalar_t__ jiffies_to_msecs (unsigned long) ; 
 unsigned long msecs_to_jiffies (scalar_t__) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int,int*,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int,unsigned int*) ; 
 int regmap_write (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  time_after (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int it913x_init(struct dvb_frontend *fe)
{
	struct it913x_dev *dev = fe->tuner_priv;
	struct platform_device *pdev = dev->pdev;
	int ret;
	unsigned int utmp;
	u8 iqik_m_cal, nv_val, buf[2];
	static const u8 nv[] = {48, 32, 24, 16, 12, 8, 6, 4, 2};
	unsigned long timeout;

	dev_dbg(&pdev->dev, "role %u\n", dev->role);

	ret = regmap_write(dev->regmap, 0x80ec4c, 0x68);
	if (ret)
		goto err;

	usleep_range(10000, 100000);

	ret = regmap_read(dev->regmap, 0x80ec86, &utmp);
	if (ret)
		goto err;

	switch (utmp) {
	case 0:
		/* 12.000 MHz */
		dev->clk_mode = utmp;
		dev->xtal = 2000;
		dev->fdiv = 3;
		iqik_m_cal = 16;
		break;
	case 1:
		/* 20.480 MHz */
		dev->clk_mode = utmp;
		dev->xtal = 640;
		dev->fdiv = 1;
		iqik_m_cal = 6;
		break;
	default:
		dev_err(&pdev->dev, "unknown clock identifier %d\n", utmp);
		goto err;
	}

	ret = regmap_read(dev->regmap, 0x80ed03,  &utmp);
	if (ret)
		goto err;

	else if (utmp < ARRAY_SIZE(nv))
		nv_val = nv[utmp];
	else
		nv_val = 2;

	#define TIMEOUT 50
	timeout = jiffies + msecs_to_jiffies(TIMEOUT);
	while (!time_after(jiffies, timeout)) {
		ret = regmap_bulk_read(dev->regmap, 0x80ed23, buf, 2);
		if (ret)
			goto err;

		utmp = (buf[1] << 8) | (buf[0] << 0);
		if (utmp)
			break;
	}

	dev_dbg(&pdev->dev, "r_fbc_m_bdry took %u ms, val %u\n",
			jiffies_to_msecs(jiffies) -
			(jiffies_to_msecs(timeout) - TIMEOUT), utmp);

	dev->fn_min = dev->xtal * utmp;
	dev->fn_min /= (dev->fdiv * nv_val);
	dev->fn_min *= 1000;
	dev_dbg(&pdev->dev, "fn_min %u\n", dev->fn_min);

	/*
	 * Chip version BX never sets that flag so we just wait 50ms in that
	 * case. It is possible poll BX similarly than AX and then timeout in
	 * order to get 50ms delay, but that causes about 120 extra I2C
	 * messages. As for now, we just wait and reduce IO.
	 */
	if (dev->chip_ver == 1) {
		#define TIMEOUT 50
		timeout = jiffies + msecs_to_jiffies(TIMEOUT);
		while (!time_after(jiffies, timeout)) {
			ret = regmap_read(dev->regmap, 0x80ec82, &utmp);
			if (ret)
				goto err;

			if (utmp)
				break;
		}

		dev_dbg(&pdev->dev, "p_tsm_init_mode took %u ms, val %u\n",
				jiffies_to_msecs(jiffies) -
				(jiffies_to_msecs(timeout) - TIMEOUT), utmp);
	} else {
		msleep(50);
	}

	ret = regmap_write(dev->regmap, 0x80ed81, iqik_m_cal);
	if (ret)
		goto err;

	ret = regmap_write(dev->regmap, 0x80ec57, 0x00);
	if (ret)
		goto err;

	ret = regmap_write(dev->regmap, 0x80ec58, 0x00);
	if (ret)
		goto err;

	ret = regmap_write(dev->regmap, 0x80ec40, 0x01);
	if (ret)
		goto err;

	dev->active = true;

	return 0;
err:
	dev_dbg(&pdev->dev, "failed %d\n", ret);
	return ret;
}