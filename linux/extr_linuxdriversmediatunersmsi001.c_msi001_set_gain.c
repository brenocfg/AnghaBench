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
typedef  int u32 ;
struct spi_device {int /*<<< orphan*/  dev; } ;
struct msi001_dev {struct spi_device* spi; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,...) ; 
 int msi001_wreg (struct msi001_dev*,int) ; 

__attribute__((used)) static int msi001_set_gain(struct msi001_dev *dev, int lna_gain, int mixer_gain,
			   int if_gain)
{
	struct spi_device *spi = dev->spi;
	int ret;
	u32 reg;

	dev_dbg(&spi->dev, "lna=%d mixer=%d if=%d\n",
		lna_gain, mixer_gain, if_gain);

	reg = 1 << 0;
	reg |= (59 - if_gain) << 4;
	reg |= 0 << 10;
	reg |= (1 - mixer_gain) << 12;
	reg |= (1 - lna_gain) << 13;
	reg |= 4 << 14;
	reg |= 0 << 17;
	ret = msi001_wreg(dev, reg);
	if (ret)
		goto err;

	return 0;
err:
	dev_dbg(&spi->dev, "failed %d\n", ret);
	return ret;
}