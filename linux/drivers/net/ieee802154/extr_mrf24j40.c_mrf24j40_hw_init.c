#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct mrf24j40 {int /*<<< orphan*/  regmap_long; TYPE_2__* spi; int /*<<< orphan*/  regmap_short; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;
struct TYPE_3__ {scalar_t__ driver_data; } ;

/* Variables and functions */
 int BIT_INTEDGE ; 
 int IRQ_TYPE_EDGE_FALLING ; 
#define  IRQ_TYPE_EDGE_RISING 129 
#define  IRQ_TYPE_LEVEL_HIGH 128 
 scalar_t__ MRF24J40MC ; 
 int /*<<< orphan*/  REG_BBREG2 ; 
 int /*<<< orphan*/  REG_BBREG6 ; 
 int /*<<< orphan*/  REG_CCAEDTH ; 
 int /*<<< orphan*/  REG_GPIO ; 
 int /*<<< orphan*/  REG_PACON2 ; 
 int /*<<< orphan*/  REG_RFCON0 ; 
 int /*<<< orphan*/  REG_RFCON1 ; 
 int /*<<< orphan*/  REG_RFCON2 ; 
 int /*<<< orphan*/  REG_RFCON3 ; 
 int /*<<< orphan*/  REG_RFCON6 ; 
 int /*<<< orphan*/  REG_RFCON7 ; 
 int /*<<< orphan*/  REG_RFCON8 ; 
 int /*<<< orphan*/  REG_RFCTL ; 
 int /*<<< orphan*/  REG_RXMCR ; 
 int /*<<< orphan*/  REG_SLPCON0 ; 
 int /*<<< orphan*/  REG_SLPCON1 ; 
 int /*<<< orphan*/  REG_SOFTRST ; 
 int /*<<< orphan*/  REG_TESTMODE ; 
 int /*<<< orphan*/  REG_TRISGPIO ; 
 int /*<<< orphan*/  REG_TXSTBL ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int irq_get_trigger_type (int /*<<< orphan*/ ) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* spi_get_device_id (TYPE_2__*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int mrf24j40_hw_init(struct mrf24j40 *devrec)
{
	u32 irq_type;
	int ret;

	/* Initialize the device.
		From datasheet section 3.2: Initialization. */
	ret = regmap_write(devrec->regmap_short, REG_SOFTRST, 0x07);
	if (ret)
		goto err_ret;

	ret = regmap_write(devrec->regmap_short, REG_PACON2, 0x98);
	if (ret)
		goto err_ret;

	ret = regmap_write(devrec->regmap_short, REG_TXSTBL, 0x95);
	if (ret)
		goto err_ret;

	ret = regmap_write(devrec->regmap_long, REG_RFCON0, 0x03);
	if (ret)
		goto err_ret;

	ret = regmap_write(devrec->regmap_long, REG_RFCON1, 0x01);
	if (ret)
		goto err_ret;

	ret = regmap_write(devrec->regmap_long, REG_RFCON2, 0x80);
	if (ret)
		goto err_ret;

	ret = regmap_write(devrec->regmap_long, REG_RFCON6, 0x90);
	if (ret)
		goto err_ret;

	ret = regmap_write(devrec->regmap_long, REG_RFCON7, 0x80);
	if (ret)
		goto err_ret;

	ret = regmap_write(devrec->regmap_long, REG_RFCON8, 0x10);
	if (ret)
		goto err_ret;

	ret = regmap_write(devrec->regmap_long, REG_SLPCON1, 0x21);
	if (ret)
		goto err_ret;

	ret = regmap_write(devrec->regmap_short, REG_BBREG2, 0x80);
	if (ret)
		goto err_ret;

	ret = regmap_write(devrec->regmap_short, REG_CCAEDTH, 0x60);
	if (ret)
		goto err_ret;

	ret = regmap_write(devrec->regmap_short, REG_BBREG6, 0x40);
	if (ret)
		goto err_ret;

	ret = regmap_write(devrec->regmap_short, REG_RFCTL, 0x04);
	if (ret)
		goto err_ret;

	ret = regmap_write(devrec->regmap_short, REG_RFCTL, 0x0);
	if (ret)
		goto err_ret;

	udelay(192);

	/* Set RX Mode. RXMCR<1:0>: 0x0 normal, 0x1 promisc, 0x2 error */
	ret = regmap_update_bits(devrec->regmap_short, REG_RXMCR, 0x03, 0x00);
	if (ret)
		goto err_ret;

	if (spi_get_device_id(devrec->spi)->driver_data == MRF24J40MC) {
		/* Enable external amplifier.
		 * From MRF24J40MC datasheet section 1.3: Operation.
		 */
		regmap_update_bits(devrec->regmap_long, REG_TESTMODE, 0x07,
				   0x07);

		/* Set GPIO3 as output. */
		regmap_update_bits(devrec->regmap_short, REG_TRISGPIO, 0x08,
				   0x08);

		/* Set GPIO3 HIGH to enable U5 voltage regulator */
		regmap_update_bits(devrec->regmap_short, REG_GPIO, 0x08, 0x08);

		/* Reduce TX pwr to meet FCC requirements.
		 * From MRF24J40MC datasheet section 3.1.1
		 */
		regmap_write(devrec->regmap_long, REG_RFCON3, 0x28);
	}

	irq_type = irq_get_trigger_type(devrec->spi->irq);
	if (irq_type == IRQ_TYPE_EDGE_RISING ||
	    irq_type == IRQ_TYPE_EDGE_FALLING)
		dev_warn(&devrec->spi->dev,
			 "Using edge triggered irq's are not recommended, because it can cause races and result in a non-functional driver!\n");
	switch (irq_type) {
	case IRQ_TYPE_EDGE_RISING:
	case IRQ_TYPE_LEVEL_HIGH:
		/* set interrupt polarity to rising */
		ret = regmap_update_bits(devrec->regmap_long, REG_SLPCON0,
					 BIT_INTEDGE, BIT_INTEDGE);
		if (ret)
			goto err_ret;
		break;
	default:
		/* default is falling edge */
		break;
	}

	return 0;

err_ret:
	return ret;
}