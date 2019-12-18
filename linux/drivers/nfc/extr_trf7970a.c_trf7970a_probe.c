#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct trf7970a {int /*<<< orphan*/  lock; void* regulator; int /*<<< orphan*/  ddev; TYPE_1__* dev; int /*<<< orphan*/  io_ctrl; int /*<<< orphan*/  chip_status_ctrl; int /*<<< orphan*/  timeout_work; scalar_t__ modulator_sys_clk_ctrl; int /*<<< orphan*/  quirks; void* en2_gpiod; void* en_gpiod; struct spi_device* spi; int /*<<< orphan*/  state; } ;
struct TYPE_12__ {struct device_node* of_node; } ;
struct spi_device {int bits_per_word; TYPE_1__ dev; int /*<<< orphan*/  irq; int /*<<< orphan*/  mode; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_RISING ; 
 scalar_t__ IS_ERR (void*) ; 
 int NFC_DIGITAL_DRV_CAPS_IN_CRC ; 
 int NFC_DIGITAL_DRV_CAPS_TG_CRC ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  SPI_MODE_1 ; 
 scalar_t__ TRF7970A_13MHZ_CLOCK_FREQUENCY ; 
 scalar_t__ TRF7970A_27MHZ_CLOCK_FREQUENCY ; 
 int /*<<< orphan*/  TRF7970A_CHIP_STATUS_VRS5_3 ; 
 scalar_t__ TRF7970A_MODULATOR_27MHZ ; 
 int /*<<< orphan*/  TRF7970A_QUIRK_EN2_MUST_STAY_LOW ; 
 int /*<<< orphan*/  TRF7970A_QUIRK_IRQ_STATUS_READ ; 
 int /*<<< orphan*/  TRF7970A_REG_IO_CTRL_IO_LOW ; 
 int /*<<< orphan*/  TRF7970A_ST_PWR_OFF ; 
 int /*<<< orphan*/  TRF7970A_SUPPORTED_PROTOCOLS ; 
 int /*<<< orphan*/  dev_dbg (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*) ; 
 void* devm_gpiod_get_index (TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* devm_gpiod_get_index_optional (TYPE_1__*,char*,int,int /*<<< orphan*/ ) ; 
 struct trf7970a* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 void* devm_regulator_get (TYPE_1__*,char*) ; 
 int devm_request_threaded_irq (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,struct trf7970a*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfc_digital_allocate_device (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfc_digital_free_device (int /*<<< orphan*/ ) ; 
 int nfc_digital_register_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfc_digital_set_drvdata (int /*<<< orphan*/ ,struct trf7970a*) ; 
 int /*<<< orphan*/  nfc_digital_set_parent_dev (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ of_property_read_bool (struct device_node*,char*) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,scalar_t__*) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (TYPE_1__*,int) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (TYPE_1__*) ; 
 int /*<<< orphan*/  regulator_disable (void*) ; 
 int regulator_enable (void*) ; 
 int regulator_get_voltage (void*) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct trf7970a*) ; 
 int spi_setup (struct spi_device*) ; 
 int trf7970a_get_autosuspend_delay (struct device_node*) ; 
 int /*<<< orphan*/  trf7970a_irq ; 
 int /*<<< orphan*/  trf7970a_nfc_ops ; 
 int /*<<< orphan*/  trf7970a_shutdown (struct trf7970a*) ; 
 int trf7970a_startup (struct trf7970a*) ; 
 int /*<<< orphan*/  trf7970a_timeout_work_handler ; 

__attribute__((used)) static int trf7970a_probe(struct spi_device *spi)
{
	struct device_node *np = spi->dev.of_node;
	struct trf7970a *trf;
	int uvolts, autosuspend_delay, ret;
	u32 clk_freq = TRF7970A_13MHZ_CLOCK_FREQUENCY;

	if (!np) {
		dev_err(&spi->dev, "No Device Tree entry\n");
		return -EINVAL;
	}

	trf = devm_kzalloc(&spi->dev, sizeof(*trf), GFP_KERNEL);
	if (!trf)
		return -ENOMEM;

	trf->state = TRF7970A_ST_PWR_OFF;
	trf->dev = &spi->dev;
	trf->spi = spi;

	spi->mode = SPI_MODE_1;
	spi->bits_per_word = 8;

	ret = spi_setup(spi);
	if (ret < 0) {
		dev_err(trf->dev, "Can't set up SPI Communication\n");
		return ret;
	}

	if (of_property_read_bool(np, "irq-status-read-quirk"))
		trf->quirks |= TRF7970A_QUIRK_IRQ_STATUS_READ;

	/* There are two enable pins - only EN must be present in the DT */
	trf->en_gpiod = devm_gpiod_get_index(trf->dev, "ti,enable", 0,
					     GPIOD_OUT_LOW);
	if (IS_ERR(trf->en_gpiod)) {
		dev_err(trf->dev, "No EN GPIO property\n");
		return PTR_ERR(trf->en_gpiod);
	}

	trf->en2_gpiod = devm_gpiod_get_index_optional(trf->dev, "ti,enable", 1,
						       GPIOD_OUT_LOW);
	if (!trf->en2_gpiod) {
		dev_info(trf->dev, "No EN2 GPIO property\n");
	} else if (IS_ERR(trf->en2_gpiod)) {
		dev_err(trf->dev, "Error getting EN2 GPIO property: %ld\n",
			PTR_ERR(trf->en2_gpiod));
		return PTR_ERR(trf->en2_gpiod);
	} else if (of_property_read_bool(np, "en2-rf-quirk")) {
		trf->quirks |= TRF7970A_QUIRK_EN2_MUST_STAY_LOW;
	}

	of_property_read_u32(np, "clock-frequency", &clk_freq);
	if ((clk_freq != TRF7970A_27MHZ_CLOCK_FREQUENCY) &&
	    (clk_freq != TRF7970A_13MHZ_CLOCK_FREQUENCY)) {
		dev_err(trf->dev,
			"clock-frequency (%u Hz) unsupported\n", clk_freq);
		return -EINVAL;
	}

	if (clk_freq == TRF7970A_27MHZ_CLOCK_FREQUENCY) {
		trf->modulator_sys_clk_ctrl = TRF7970A_MODULATOR_27MHZ;
		dev_dbg(trf->dev, "trf7970a configured for 27MHz crystal\n");
	} else {
		trf->modulator_sys_clk_ctrl = 0;
	}

	ret = devm_request_threaded_irq(trf->dev, spi->irq, NULL,
					trf7970a_irq,
					IRQF_TRIGGER_RISING | IRQF_ONESHOT,
					"trf7970a", trf);
	if (ret) {
		dev_err(trf->dev, "Can't request IRQ#%d: %d\n", spi->irq, ret);
		return ret;
	}

	mutex_init(&trf->lock);
	INIT_DELAYED_WORK(&trf->timeout_work, trf7970a_timeout_work_handler);

	trf->regulator = devm_regulator_get(&spi->dev, "vin");
	if (IS_ERR(trf->regulator)) {
		ret = PTR_ERR(trf->regulator);
		dev_err(trf->dev, "Can't get VIN regulator: %d\n", ret);
		goto err_destroy_lock;
	}

	ret = regulator_enable(trf->regulator);
	if (ret) {
		dev_err(trf->dev, "Can't enable VIN: %d\n", ret);
		goto err_destroy_lock;
	}

	uvolts = regulator_get_voltage(trf->regulator);
	if (uvolts > 4000000)
		trf->chip_status_ctrl = TRF7970A_CHIP_STATUS_VRS5_3;

	trf->regulator = devm_regulator_get(&spi->dev, "vdd-io");
	if (IS_ERR(trf->regulator)) {
		ret = PTR_ERR(trf->regulator);
		dev_err(trf->dev, "Can't get VDD_IO regulator: %d\n", ret);
		goto err_destroy_lock;
	}

	ret = regulator_enable(trf->regulator);
	if (ret) {
		dev_err(trf->dev, "Can't enable VDD_IO: %d\n", ret);
		goto err_destroy_lock;
	}

	if (regulator_get_voltage(trf->regulator) == 1800000) {
		trf->io_ctrl = TRF7970A_REG_IO_CTRL_IO_LOW;
		dev_dbg(trf->dev, "trf7970a config vdd_io to 1.8V\n");
	}

	trf->ddev = nfc_digital_allocate_device(&trf7970a_nfc_ops,
						TRF7970A_SUPPORTED_PROTOCOLS,
						NFC_DIGITAL_DRV_CAPS_IN_CRC |
						NFC_DIGITAL_DRV_CAPS_TG_CRC, 0,
						0);
	if (!trf->ddev) {
		dev_err(trf->dev, "Can't allocate NFC digital device\n");
		ret = -ENOMEM;
		goto err_disable_regulator;
	}

	nfc_digital_set_parent_dev(trf->ddev, trf->dev);
	nfc_digital_set_drvdata(trf->ddev, trf);
	spi_set_drvdata(spi, trf);

	autosuspend_delay = trf7970a_get_autosuspend_delay(np);

	pm_runtime_set_autosuspend_delay(trf->dev, autosuspend_delay);
	pm_runtime_use_autosuspend(trf->dev);

	ret = trf7970a_startup(trf);
	if (ret)
		goto err_free_ddev;

	ret = nfc_digital_register_device(trf->ddev);
	if (ret) {
		dev_err(trf->dev, "Can't register NFC digital device: %d\n",
			ret);
		goto err_shutdown;
	}

	return 0;

err_shutdown:
	trf7970a_shutdown(trf);
err_free_ddev:
	nfc_digital_free_device(trf->ddev);
err_disable_regulator:
	regulator_disable(trf->regulator);
err_destroy_lock:
	mutex_destroy(&trf->lock);
	return ret;
}