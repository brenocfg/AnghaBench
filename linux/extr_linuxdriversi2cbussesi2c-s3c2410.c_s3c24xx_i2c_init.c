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
struct s3c24xx_i2c {scalar_t__ regs; int /*<<< orphan*/  dev; struct s3c2410_platform_i2c* pdata; } ;
struct s3c2410_platform_i2c {unsigned int slave_addr; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ S3C2410_IICADD ; 
 scalar_t__ S3C2410_IICCON ; 
 scalar_t__ S3C2410_IICSTAT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 scalar_t__ s3c24xx_i2c_clockrate (struct s3c24xx_i2c*,unsigned int*) ; 
 int /*<<< orphan*/  writeb (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int s3c24xx_i2c_init(struct s3c24xx_i2c *i2c)
{
	struct s3c2410_platform_i2c *pdata;
	unsigned int freq;

	/* get the plafrom data */

	pdata = i2c->pdata;

	/* write slave address */

	writeb(pdata->slave_addr, i2c->regs + S3C2410_IICADD);

	dev_info(i2c->dev, "slave address 0x%02x\n", pdata->slave_addr);

	writel(0, i2c->regs + S3C2410_IICCON);
	writel(0, i2c->regs + S3C2410_IICSTAT);

	/* we need to work out the divisors for the clock... */

	if (s3c24xx_i2c_clockrate(i2c, &freq) != 0) {
		dev_err(i2c->dev, "cannot meet bus frequency required\n");
		return -EINVAL;
	}

	/* todo - check that the i2c lines aren't being dragged anywhere */

	dev_info(i2c->dev, "bus frequency set to %d KHz\n", freq);
	dev_dbg(i2c->dev, "S3C2410_IICCON=0x%02x\n",
		readl(i2c->regs + S3C2410_IICCON));

	return 0;
}