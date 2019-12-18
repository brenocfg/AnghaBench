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
struct spi_device {int bits_per_word; scalar_t__ irq; int /*<<< orphan*/  dev; int /*<<< orphan*/  mode; } ;
struct rtc_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_FALLING ; 
 scalar_t__ IS_ERR (struct rtc_device*) ; 
 int /*<<< orphan*/  MCP795_24_BIT ; 
 int /*<<< orphan*/  MCP795_ALM0IF_BIT ; 
 int MCP795_REG_ALM0_DAY ; 
 int PTR_ERR (struct rtc_device*) ; 
 int /*<<< orphan*/  SPI_MODE_0 ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_init_wakeup (int /*<<< orphan*/ *,int) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct spi_device*) ; 
 struct rtc_device* devm_rtc_device_register (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcp795_irq ; 
 int /*<<< orphan*/  mcp795_rtc_ops ; 
 int /*<<< orphan*/  mcp795_rtcc_set_bits (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcp795_start_oscillator (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct rtc_device*) ; 
 int spi_setup (struct spi_device*) ; 

__attribute__((used)) static int mcp795_probe(struct spi_device *spi)
{
	struct rtc_device *rtc;
	int ret;

	spi->mode = SPI_MODE_0;
	spi->bits_per_word = 8;
	ret = spi_setup(spi);
	if (ret) {
		dev_err(&spi->dev, "Unable to setup SPI\n");
		return ret;
	}

	/* Start the oscillator but don't set the value of EXTOSC bit */
	mcp795_start_oscillator(&spi->dev, NULL);
	/* Clear the 12 hour mode flag*/
	mcp795_rtcc_set_bits(&spi->dev, 0x03, MCP795_24_BIT, 0);

	rtc = devm_rtc_device_register(&spi->dev, "rtc-mcp795",
					&mcp795_rtc_ops, THIS_MODULE);
	if (IS_ERR(rtc))
		return PTR_ERR(rtc);

	spi_set_drvdata(spi, rtc);

	if (spi->irq > 0) {
		dev_dbg(&spi->dev, "Alarm support enabled\n");

		/* Clear any pending alarm (ALM0IF bit) before requesting
		 * the interrupt.
		 */
		mcp795_rtcc_set_bits(&spi->dev, MCP795_REG_ALM0_DAY,
					MCP795_ALM0IF_BIT, 0);
		ret = devm_request_threaded_irq(&spi->dev, spi->irq, NULL,
				mcp795_irq, IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
				dev_name(&rtc->dev), spi);
		if (ret)
			dev_err(&spi->dev, "Failed to request IRQ: %d: %d\n",
						spi->irq, ret);
		else
			device_init_wakeup(&spi->dev, true);
	}
	return 0;
}