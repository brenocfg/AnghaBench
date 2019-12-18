#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  value ;
typedef  int u8 ;
struct spi_device {int bits_per_word; int max_speed_hz; int mode; int /*<<< orphan*/  dev; scalar_t__ irq; } ;
struct nvmem_config {char* name; int word_size; int stride; struct ds1305* priv; int /*<<< orphan*/  reg_write; int /*<<< orphan*/  reg_read; int /*<<< orphan*/  size; } ;
struct ds1305_platform_data {int trickle; scalar_t__ en_1hz; scalar_t__ is_ds1306; } ;
struct ds1305 {int* ctrl; int hr12; TYPE_1__* rtc; int /*<<< orphan*/  work; struct spi_device* spi; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  addr ;
struct TYPE_6__ {int nvram_old_abi; int /*<<< orphan*/  dev; int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 int DS1305_CONTROL ; 
 int DS1305_HOUR ; 
 int DS1305_HR_12 ; 
 int /*<<< orphan*/  DS1305_NVRAM_LEN ; 
 int DS1305_TRICKLE_MAGIC ; 
 int DS1305_WP ; 
 int DS1305_WRITE ; 
 int DS1305_nEOSC ; 
 int DS1306_1HZ ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (TYPE_1__*) ; 
 int PTR_ERR (TYPE_1__*) ; 
 int SPI_CPHA ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,scalar_t__,int) ; 
 struct ds1305_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  device_set_wakeup_capable (int /*<<< orphan*/ *,int) ; 
 struct ds1305* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ds1305*) ; 
 TYPE_1__* devm_rtc_allocate_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ds1305_irq ; 
 int /*<<< orphan*/  ds1305_nvram_read ; 
 int /*<<< orphan*/  ds1305_nvram_write ; 
 int /*<<< orphan*/  ds1305_ops ; 
 int /*<<< orphan*/  ds1305_work ; 
 int /*<<< orphan*/  rtc_nvmem_register (TYPE_1__*,struct nvmem_config*) ; 
 int rtc_register_device (TYPE_1__*) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct ds1305*) ; 
 int spi_write_then_read (struct spi_device*,int*,int,int*,int) ; 

__attribute__((used)) static int ds1305_probe(struct spi_device *spi)
{
	struct ds1305			*ds1305;
	int				status;
	u8				addr, value;
	struct ds1305_platform_data	*pdata = dev_get_platdata(&spi->dev);
	bool				write_ctrl = false;
	struct nvmem_config ds1305_nvmem_cfg = {
		.name = "ds1305_nvram",
		.word_size = 1,
		.stride = 1,
		.size = DS1305_NVRAM_LEN,
		.reg_read = ds1305_nvram_read,
		.reg_write = ds1305_nvram_write,
	};

	/* Sanity check board setup data.  This may be hooked up
	 * in 3wire mode, but we don't care.  Note that unless
	 * there's an inverter in place, this needs SPI_CS_HIGH!
	 */
	if ((spi->bits_per_word && spi->bits_per_word != 8)
			|| (spi->max_speed_hz > 2000000)
			|| !(spi->mode & SPI_CPHA))
		return -EINVAL;

	/* set up driver data */
	ds1305 = devm_kzalloc(&spi->dev, sizeof(*ds1305), GFP_KERNEL);
	if (!ds1305)
		return -ENOMEM;
	ds1305->spi = spi;
	spi_set_drvdata(spi, ds1305);

	/* read and cache control registers */
	addr = DS1305_CONTROL;
	status = spi_write_then_read(spi, &addr, sizeof(addr),
			ds1305->ctrl, sizeof(ds1305->ctrl));
	if (status < 0) {
		dev_dbg(&spi->dev, "can't %s, %d\n",
				"read", status);
		return status;
	}

	dev_dbg(&spi->dev, "ctrl %s: %3ph\n", "read", ds1305->ctrl);

	/* Sanity check register values ... partially compensating for the
	 * fact that SPI has no device handshake.  A pullup on MISO would
	 * make these tests fail; but not all systems will have one.  If
	 * some register is neither 0x00 nor 0xff, a chip is likely there.
	 */
	if ((ds1305->ctrl[0] & 0x38) != 0 || (ds1305->ctrl[1] & 0xfc) != 0) {
		dev_dbg(&spi->dev, "RTC chip is not present\n");
		return -ENODEV;
	}
	if (ds1305->ctrl[2] == 0)
		dev_dbg(&spi->dev, "chip may not be present\n");

	/* enable writes if needed ... if we were paranoid it would
	 * make sense to enable them only when absolutely necessary.
	 */
	if (ds1305->ctrl[0] & DS1305_WP) {
		u8		buf[2];

		ds1305->ctrl[0] &= ~DS1305_WP;

		buf[0] = DS1305_WRITE | DS1305_CONTROL;
		buf[1] = ds1305->ctrl[0];
		status = spi_write_then_read(spi, buf, sizeof(buf), NULL, 0);

		dev_dbg(&spi->dev, "clear WP --> %d\n", status);
		if (status < 0)
			return status;
	}

	/* on DS1305, maybe start oscillator; like most low power
	 * oscillators, it may take a second to stabilize
	 */
	if (ds1305->ctrl[0] & DS1305_nEOSC) {
		ds1305->ctrl[0] &= ~DS1305_nEOSC;
		write_ctrl = true;
		dev_warn(&spi->dev, "SET TIME!\n");
	}

	/* ack any pending IRQs */
	if (ds1305->ctrl[1]) {
		ds1305->ctrl[1] = 0;
		write_ctrl = true;
	}

	/* this may need one-time (re)init */
	if (pdata) {
		/* maybe enable trickle charge */
		if (((ds1305->ctrl[2] & 0xf0) != DS1305_TRICKLE_MAGIC)) {
			ds1305->ctrl[2] = DS1305_TRICKLE_MAGIC
						| pdata->trickle;
			write_ctrl = true;
		}

		/* on DS1306, configure 1 Hz signal */
		if (pdata->is_ds1306) {
			if (pdata->en_1hz) {
				if (!(ds1305->ctrl[0] & DS1306_1HZ)) {
					ds1305->ctrl[0] |= DS1306_1HZ;
					write_ctrl = true;
				}
			} else {
				if (ds1305->ctrl[0] & DS1306_1HZ) {
					ds1305->ctrl[0] &= ~DS1306_1HZ;
					write_ctrl = true;
				}
			}
		}
	}

	if (write_ctrl) {
		u8		buf[4];

		buf[0] = DS1305_WRITE | DS1305_CONTROL;
		buf[1] = ds1305->ctrl[0];
		buf[2] = ds1305->ctrl[1];
		buf[3] = ds1305->ctrl[2];
		status = spi_write_then_read(spi, buf, sizeof(buf), NULL, 0);
		if (status < 0) {
			dev_dbg(&spi->dev, "can't %s, %d\n",
					"write", status);
			return status;
		}

		dev_dbg(&spi->dev, "ctrl %s: %3ph\n", "write", ds1305->ctrl);
	}

	/* see if non-Linux software set up AM/PM mode */
	addr = DS1305_HOUR;
	status = spi_write_then_read(spi, &addr, sizeof(addr),
				&value, sizeof(value));
	if (status < 0) {
		dev_dbg(&spi->dev, "read HOUR --> %d\n", status);
		return status;
	}

	ds1305->hr12 = (DS1305_HR_12 & value) != 0;
	if (ds1305->hr12)
		dev_dbg(&spi->dev, "AM/PM\n");

	/* register RTC ... from here on, ds1305->ctrl needs locking */
	ds1305->rtc = devm_rtc_allocate_device(&spi->dev);
	if (IS_ERR(ds1305->rtc))
		return PTR_ERR(ds1305->rtc);

	ds1305->rtc->ops = &ds1305_ops;

	ds1305_nvmem_cfg.priv = ds1305;
	ds1305->rtc->nvram_old_abi = true;
	status = rtc_register_device(ds1305->rtc);
	if (status)
		return status;

	rtc_nvmem_register(ds1305->rtc, &ds1305_nvmem_cfg);

	/* Maybe set up alarm IRQ; be ready to handle it triggering right
	 * away.  NOTE that we don't share this.  The signal is active low,
	 * and we can't ack it before a SPI message delay.  We temporarily
	 * disable the IRQ until it's acked, which lets us work with more
	 * IRQ trigger modes (not all IRQ controllers can do falling edge).
	 */
	if (spi->irq) {
		INIT_WORK(&ds1305->work, ds1305_work);
		status = devm_request_irq(&spi->dev, spi->irq, ds1305_irq,
				0, dev_name(&ds1305->rtc->dev), ds1305);
		if (status < 0) {
			dev_err(&spi->dev, "request_irq %d --> %d\n",
					spi->irq, status);
		} else {
			device_set_wakeup_capable(&spi->dev, 1);
		}
	}

	return 0;
}