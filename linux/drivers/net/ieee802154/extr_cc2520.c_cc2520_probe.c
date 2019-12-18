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
struct spi_device {int /*<<< orphan*/  dev; } ;
struct cc2520_private {int amplified; int /*<<< orphan*/  fifop_irqwork; int /*<<< orphan*/  buffer_mutex; int /*<<< orphan*/  tx_complete; int /*<<< orphan*/  lock; void* buf; struct spi_device* spi; } ;
struct cc2520_platform_data {int /*<<< orphan*/  sfd; int /*<<< orphan*/  fifop; int /*<<< orphan*/  reset; int /*<<< orphan*/  vreg; int /*<<< orphan*/  cca; int /*<<< orphan*/  fifo; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOF_IN ; 
 int /*<<< orphan*/  GPIOF_OUT_INIT_LOW ; 
 int /*<<< orphan*/  HIGH ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQF_TRIGGER_FALLING ; 
 int /*<<< orphan*/  IRQF_TRIGGER_RISING ; 
 int SPI_COMMAND_BUFFER ; 
 int /*<<< orphan*/  cc2520_fifop_irqwork ; 
 int /*<<< orphan*/  cc2520_fifop_isr ; 
 int cc2520_get_platform_data (struct spi_device*,struct cc2520_platform_data*) ; 
 int cc2520_hw_init (struct cc2520_private*) ; 
 int cc2520_register (struct cc2520_private*) ; 
 int /*<<< orphan*/  cc2520_sfd_isr ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int devm_gpio_request_one (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 void* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cc2520_private*) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_to_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct cc2520_private*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int cc2520_probe(struct spi_device *spi)
{
	struct cc2520_private *priv;
	struct cc2520_platform_data pdata;
	int ret;

	priv = devm_kzalloc(&spi->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	spi_set_drvdata(spi, priv);

	ret = cc2520_get_platform_data(spi, &pdata);
	if (ret < 0) {
		dev_err(&spi->dev, "no platform data\n");
		return -EINVAL;
	}

	priv->spi = spi;

	priv->buf = devm_kzalloc(&spi->dev,
				 SPI_COMMAND_BUFFER, GFP_KERNEL);
	if (!priv->buf)
		return -ENOMEM;

	mutex_init(&priv->buffer_mutex);
	INIT_WORK(&priv->fifop_irqwork, cc2520_fifop_irqwork);
	spin_lock_init(&priv->lock);
	init_completion(&priv->tx_complete);

	/* Assumption that CC2591 is not connected */
	priv->amplified = false;

	/* Request all the gpio's */
	if (!gpio_is_valid(pdata.fifo)) {
		dev_err(&spi->dev, "fifo gpio is not valid\n");
		ret = -EINVAL;
		goto err_hw_init;
	}

	ret = devm_gpio_request_one(&spi->dev, pdata.fifo,
				    GPIOF_IN, "fifo");
	if (ret)
		goto err_hw_init;

	if (!gpio_is_valid(pdata.cca)) {
		dev_err(&spi->dev, "cca gpio is not valid\n");
		ret = -EINVAL;
		goto err_hw_init;
	}

	ret = devm_gpio_request_one(&spi->dev, pdata.cca,
				    GPIOF_IN, "cca");
	if (ret)
		goto err_hw_init;

	if (!gpio_is_valid(pdata.fifop)) {
		dev_err(&spi->dev, "fifop gpio is not valid\n");
		ret = -EINVAL;
		goto err_hw_init;
	}

	ret = devm_gpio_request_one(&spi->dev, pdata.fifop,
				    GPIOF_IN, "fifop");
	if (ret)
		goto err_hw_init;

	if (!gpio_is_valid(pdata.sfd)) {
		dev_err(&spi->dev, "sfd gpio is not valid\n");
		ret = -EINVAL;
		goto err_hw_init;
	}

	ret = devm_gpio_request_one(&spi->dev, pdata.sfd,
				    GPIOF_IN, "sfd");
	if (ret)
		goto err_hw_init;

	if (!gpio_is_valid(pdata.reset)) {
		dev_err(&spi->dev, "reset gpio is not valid\n");
		ret = -EINVAL;
		goto err_hw_init;
	}

	ret = devm_gpio_request_one(&spi->dev, pdata.reset,
				    GPIOF_OUT_INIT_LOW, "reset");
	if (ret)
		goto err_hw_init;

	if (!gpio_is_valid(pdata.vreg)) {
		dev_err(&spi->dev, "vreg gpio is not valid\n");
		ret = -EINVAL;
		goto err_hw_init;
	}

	ret = devm_gpio_request_one(&spi->dev, pdata.vreg,
				    GPIOF_OUT_INIT_LOW, "vreg");
	if (ret)
		goto err_hw_init;

	gpio_set_value(pdata.vreg, HIGH);
	usleep_range(100, 150);

	gpio_set_value(pdata.reset, HIGH);
	usleep_range(200, 250);

	ret = cc2520_hw_init(priv);
	if (ret)
		goto err_hw_init;

	/* Set up fifop interrupt */
	ret = devm_request_irq(&spi->dev,
			       gpio_to_irq(pdata.fifop),
			       cc2520_fifop_isr,
			       IRQF_TRIGGER_RISING,
			       dev_name(&spi->dev),
			       priv);
	if (ret) {
		dev_err(&spi->dev, "could not get fifop irq\n");
		goto err_hw_init;
	}

	/* Set up sfd interrupt */
	ret = devm_request_irq(&spi->dev,
			       gpio_to_irq(pdata.sfd),
			       cc2520_sfd_isr,
			       IRQF_TRIGGER_FALLING,
			       dev_name(&spi->dev),
			       priv);
	if (ret) {
		dev_err(&spi->dev, "could not get sfd irq\n");
		goto err_hw_init;
	}

	ret = cc2520_register(priv);
	if (ret)
		goto err_hw_init;

	return 0;

err_hw_init:
	mutex_destroy(&priv->buffer_mutex);
	flush_work(&priv->fifop_irqwork);
	return ret;
}