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
typedef  unsigned int u32 ;
struct s3c24xx_i2c {unsigned long clkrate; int quirks; scalar_t__ regs; int /*<<< orphan*/  dev; int /*<<< orphan*/  clk; struct s3c2410_platform_i2c* pdata; } ;
struct s3c2410_platform_i2c {unsigned long frequency; int sda_delay; } ;

/* Variables and functions */
 unsigned long DIV_ROUND_UP (unsigned long,int) ; 
 int EINVAL ; 
 int QUIRK_POLL ; 
 int QUIRK_S3C2440 ; 
 scalar_t__ S3C2410_IICCON ; 
 unsigned int S3C2410_IICCON_SCALE (int) ; 
 unsigned int S3C2410_IICCON_SCALEMASK ; 
 unsigned int S3C2410_IICCON_TXDIV_512 ; 
 unsigned long S3C2410_IICLC_FILTER_ON ; 
 scalar_t__ S3C2440_IICLC ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned long) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned long,int) ; 
 unsigned int readl (scalar_t__) ; 
 int s3c24xx_i2c_calcdivisor (unsigned long,unsigned long,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  writel (unsigned long,scalar_t__) ; 

__attribute__((used)) static int s3c24xx_i2c_clockrate(struct s3c24xx_i2c *i2c, unsigned int *got)
{
	struct s3c2410_platform_i2c *pdata = i2c->pdata;
	unsigned long clkin = clk_get_rate(i2c->clk);
	unsigned int divs, div1;
	unsigned long target_frequency;
	u32 iiccon;
	int freq;

	i2c->clkrate = clkin;
	clkin /= 1000;		/* clkin now in KHz */

	dev_dbg(i2c->dev, "pdata desired frequency %lu\n", pdata->frequency);

	target_frequency = pdata->frequency ? pdata->frequency : 100000;

	target_frequency /= 1000; /* Target frequency now in KHz */

	freq = s3c24xx_i2c_calcdivisor(clkin, target_frequency, &div1, &divs);

	if (freq > target_frequency) {
		dev_err(i2c->dev,
			"Unable to achieve desired frequency %luKHz."	\
			" Lowest achievable %dKHz\n", target_frequency, freq);
		return -EINVAL;
	}

	*got = freq;

	iiccon = readl(i2c->regs + S3C2410_IICCON);
	iiccon &= ~(S3C2410_IICCON_SCALEMASK | S3C2410_IICCON_TXDIV_512);
	iiccon |= (divs-1);

	if (div1 == 512)
		iiccon |= S3C2410_IICCON_TXDIV_512;

	if (i2c->quirks & QUIRK_POLL)
		iiccon |= S3C2410_IICCON_SCALE(2);

	writel(iiccon, i2c->regs + S3C2410_IICCON);

	if (i2c->quirks & QUIRK_S3C2440) {
		unsigned long sda_delay;

		if (pdata->sda_delay) {
			sda_delay = clkin * pdata->sda_delay;
			sda_delay = DIV_ROUND_UP(sda_delay, 1000000);
			sda_delay = DIV_ROUND_UP(sda_delay, 5);
			if (sda_delay > 3)
				sda_delay = 3;
			sda_delay |= S3C2410_IICLC_FILTER_ON;
		} else
			sda_delay = 0;

		dev_dbg(i2c->dev, "IICLC=%08lx\n", sda_delay);
		writel(sda_delay, i2c->regs + S3C2440_IICLC);
	}

	return 0;
}