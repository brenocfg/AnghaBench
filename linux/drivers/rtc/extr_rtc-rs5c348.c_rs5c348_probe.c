#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct rs5c348_plat_data* platform_data; } ;
struct spi_device {int max_speed_hz; TYPE_1__ dev; } ;
struct rtc_device {int /*<<< orphan*/ * ops; } ;
struct rs5c348_plat_data {int rtc_24h; struct rtc_device* rtc; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct rtc_device*) ; 
 int PTR_ERR (struct rtc_device*) ; 
 int RS5C348_BIT_24H ; 
 int /*<<< orphan*/  RS5C348_CMD_R (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RS5C348_REG_CTL1 ; 
 int /*<<< orphan*/  RS5C348_REG_SECS ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*,int) ; 
 struct rs5c348_plat_data* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 struct rtc_device* devm_rtc_allocate_device (TYPE_1__*) ; 
 int /*<<< orphan*/  rs5c348_rtc_ops ; 
 int rtc_register_device (struct rtc_device*) ; 
 int spi_w8r8 (struct spi_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rs5c348_probe(struct spi_device *spi)
{
	int ret;
	struct rtc_device *rtc;
	struct rs5c348_plat_data *pdata;

	pdata = devm_kzalloc(&spi->dev, sizeof(struct rs5c348_plat_data),
				GFP_KERNEL);
	if (!pdata)
		return -ENOMEM;
	spi->dev.platform_data = pdata;

	/* Check D7 of SECOND register */
	ret = spi_w8r8(spi, RS5C348_CMD_R(RS5C348_REG_SECS));
	if (ret < 0 || (ret & 0x80)) {
		dev_err(&spi->dev, "not found.\n");
		return ret;
	}

	dev_info(&spi->dev, "spiclk %u KHz.\n",
		 (spi->max_speed_hz + 500) / 1000);

	ret = spi_w8r8(spi, RS5C348_CMD_R(RS5C348_REG_CTL1));
	if (ret < 0)
		return ret;
	if (ret & RS5C348_BIT_24H)
		pdata->rtc_24h = 1;

	rtc = devm_rtc_allocate_device(&spi->dev);
	if (IS_ERR(rtc))
		return PTR_ERR(rtc);

	pdata->rtc = rtc;

	rtc->ops = &rs5c348_rtc_ops;

	return rtc_register_device(rtc);
}