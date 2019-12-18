#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_16__ ;

/* Type definitions */
struct st95hf_spi_context {int /*<<< orphan*/  spi_lock; int /*<<< orphan*/  done; struct spi_device* spidev; } ;
struct st95hf_context {int enable_gpio; scalar_t__ st95hf_supply; TYPE_3__* ddev; int /*<<< orphan*/  rm_lock; int /*<<< orphan*/  exchange_lock; TYPE_1__* nfcdev; int /*<<< orphan*/  fwi; struct st95hf_spi_context spicontext; } ;
struct TYPE_19__ {int /*<<< orphan*/  of_node; } ;
struct spi_device {scalar_t__ irq; TYPE_2__ dev; } ;
struct TYPE_20__ {TYPE_1__* nfc_dev; } ;
struct TYPE_18__ {TYPE_2__ dev; } ;
struct TYPE_17__ {int /*<<< orphan*/ * cmd_params; } ;

/* Variables and functions */
 size_t CMD_ISO14443A_PROTOCOL_SELECT ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int GPIOF_DIR_OUT ; 
 int GPIOF_INIT_HIGH ; 
 int /*<<< orphan*/  IRQF_TRIGGER_FALLING ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 int /*<<< orphan*/  ST95HF_CAPABILITIES ; 
 int /*<<< orphan*/  ST95HF_HEADROOM_LEN ; 
 int /*<<< orphan*/  ST95HF_SUPPORTED_PROT ; 
 int /*<<< orphan*/  ST95HF_TAILROOM_LEN ; 
 TYPE_16__* cmd_array ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_2__*,struct st95hf_spi_context*) ; 
 scalar_t__ device_property_present (TYPE_2__*,char*) ; 
 int devm_gpio_request_one (TYPE_2__*,int,int,char*) ; 
 struct st95hf_context* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ devm_regulator_get (TYPE_2__*,char*) ; 
 scalar_t__ devm_request_threaded_irq (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,void*) ; 
 int /*<<< orphan*/  gpio_is_valid (int) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 TYPE_3__* nfc_digital_allocate_device (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfc_digital_free_device (TYPE_3__*) ; 
 int nfc_digital_register_device (TYPE_3__*) ; 
 int /*<<< orphan*/  nfc_digital_set_drvdata (TYPE_3__*,struct st95hf_context*) ; 
 int /*<<< orphan*/  nfc_digital_set_parent_dev (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  nfc_info (TYPE_2__*,char*) ; 
 int of_get_named_gpio (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_disable (scalar_t__) ; 
 int regulator_enable (scalar_t__) ; 
 int /*<<< orphan*/  sema_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  st95hf_irq_handler ; 
 int /*<<< orphan*/  st95hf_irq_thread_handler ; 
 int /*<<< orphan*/  st95hf_nfc_digital_ops ; 
 int st95hf_por_sequence (struct st95hf_context*) ; 
 int st95hf_send_spi_reset_sequence (struct st95hf_context*) ; 

__attribute__((used)) static int st95hf_probe(struct spi_device *nfc_spi_dev)
{
	int ret;

	struct st95hf_context *st95context;
	struct st95hf_spi_context *spicontext;

	nfc_info(&nfc_spi_dev->dev, "ST95HF driver probe called.\n");

	st95context = devm_kzalloc(&nfc_spi_dev->dev,
				   sizeof(struct st95hf_context),
				   GFP_KERNEL);
	if (!st95context)
		return -ENOMEM;

	spicontext = &st95context->spicontext;

	spicontext->spidev = nfc_spi_dev;

	st95context->fwi =
		cmd_array[CMD_ISO14443A_PROTOCOL_SELECT].cmd_params[2];

	if (device_property_present(&nfc_spi_dev->dev, "st95hfvin")) {
		st95context->st95hf_supply =
			devm_regulator_get(&nfc_spi_dev->dev,
					   "st95hfvin");
		if (IS_ERR(st95context->st95hf_supply)) {
			dev_err(&nfc_spi_dev->dev, "failed to acquire regulator\n");
			return PTR_ERR(st95context->st95hf_supply);
		}

		ret = regulator_enable(st95context->st95hf_supply);
		if (ret) {
			dev_err(&nfc_spi_dev->dev, "failed to enable regulator\n");
			return ret;
		}
	}

	init_completion(&spicontext->done);
	mutex_init(&spicontext->spi_lock);

	/*
	 * Store spicontext in spi device object for using it in
	 * remove function
	 */
	dev_set_drvdata(&nfc_spi_dev->dev, spicontext);

	st95context->enable_gpio =
		of_get_named_gpio(nfc_spi_dev->dev.of_node,
				  "enable-gpio",
				  0);
	if (!gpio_is_valid(st95context->enable_gpio)) {
		dev_err(&nfc_spi_dev->dev, "No valid enable gpio\n");
		ret = st95context->enable_gpio;
		goto err_disable_regulator;
	}

	ret = devm_gpio_request_one(&nfc_spi_dev->dev, st95context->enable_gpio,
				    GPIOF_DIR_OUT | GPIOF_INIT_HIGH,
				    "enable_gpio");
	if (ret)
		goto err_disable_regulator;

	if (nfc_spi_dev->irq > 0) {
		if (devm_request_threaded_irq(&nfc_spi_dev->dev,
					      nfc_spi_dev->irq,
					      st95hf_irq_handler,
					      st95hf_irq_thread_handler,
					      IRQF_TRIGGER_FALLING,
					      "st95hf",
					      (void *)st95context) < 0) {
			dev_err(&nfc_spi_dev->dev, "err: irq request for st95hf is failed\n");
			ret =  -EINVAL;
			goto err_disable_regulator;
		}
	} else {
		dev_err(&nfc_spi_dev->dev, "not a valid IRQ associated with ST95HF\n");
		ret = -EINVAL;
		goto err_disable_regulator;
	}

	/*
	 * First reset SPI to handle warm reset of the system.
	 * It will put the ST95HF device in Power ON state
	 * which make the state of device identical to state
	 * at the time of cold reset of the system.
	 */
	ret = st95hf_send_spi_reset_sequence(st95context);
	if (ret) {
		dev_err(&nfc_spi_dev->dev, "err: spi_reset_sequence failed\n");
		goto err_disable_regulator;
	}

	/* call PowerOnReset sequence of ST95hf to activate it */
	ret = st95hf_por_sequence(st95context);
	if (ret) {
		dev_err(&nfc_spi_dev->dev, "err: por seq failed for st95hf\n");
		goto err_disable_regulator;
	}

	/* create NFC dev object and register with NFC Subsystem */
	st95context->ddev = nfc_digital_allocate_device(&st95hf_nfc_digital_ops,
							ST95HF_SUPPORTED_PROT,
							ST95HF_CAPABILITIES,
							ST95HF_HEADROOM_LEN,
							ST95HF_TAILROOM_LEN);
	if (!st95context->ddev) {
		ret = -ENOMEM;
		goto err_disable_regulator;
	}

	st95context->nfcdev = st95context->ddev->nfc_dev;
	nfc_digital_set_parent_dev(st95context->ddev, &nfc_spi_dev->dev);

	ret =  nfc_digital_register_device(st95context->ddev);
	if (ret) {
		dev_err(&st95context->nfcdev->dev, "st95hf registration failed\n");
		goto err_free_digital_device;
	}

	/* store st95context in nfc device object */
	nfc_digital_set_drvdata(st95context->ddev, st95context);

	sema_init(&st95context->exchange_lock, 1);
	mutex_init(&st95context->rm_lock);

	return ret;

err_free_digital_device:
	nfc_digital_free_device(st95context->ddev);
err_disable_regulator:
	if (st95context->st95hf_supply)
		regulator_disable(st95context->st95hf_supply);

	return ret;
}