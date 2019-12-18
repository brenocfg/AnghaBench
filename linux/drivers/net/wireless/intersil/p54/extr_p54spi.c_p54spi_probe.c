#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct spi_device {int bits_per_word; int max_speed_hz; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx; int /*<<< orphan*/  stop; int /*<<< orphan*/  open; } ;
struct p54s_priv {struct ieee80211_hw* hw; struct spi_device* spi; TYPE_1__ common; int /*<<< orphan*/  tx_lock; int /*<<< orphan*/  mutex; int /*<<< orphan*/  tx_pending; int /*<<< orphan*/  fw_comp; int /*<<< orphan*/  work; } ;
struct ieee80211_hw {struct p54s_priv* priv; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQ_TYPE_EDGE_RISING ; 
 int /*<<< orphan*/  SET_IEEE80211_DEV (struct ieee80211_hw*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct spi_device*) ; 
 int /*<<< orphan*/  gpio_direction_input (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_direction_output (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 int gpio_request (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gpio_to_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_set_irq_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p54_free_common (struct ieee80211_hw*) ; 
 struct ieee80211_hw* p54_init_common (int) ; 
 int p54_register_common (struct ieee80211_hw*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p54spi_gpio_irq ; 
 int /*<<< orphan*/  p54spi_gpio_power ; 
 int /*<<< orphan*/  p54spi_interrupt ; 
 int /*<<< orphan*/  p54spi_op_start ; 
 int /*<<< orphan*/  p54spi_op_stop ; 
 int /*<<< orphan*/  p54spi_op_tx ; 
 int p54spi_request_eeprom (struct ieee80211_hw*) ; 
 int p54spi_request_firmware (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  p54spi_work ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct spi_device*) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct p54s_priv*) ; 
 int spi_setup (struct spi_device*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int p54spi_probe(struct spi_device *spi)
{
	struct p54s_priv *priv = NULL;
	struct ieee80211_hw *hw;
	int ret = -EINVAL;

	hw = p54_init_common(sizeof(*priv));
	if (!hw) {
		dev_err(&spi->dev, "could not alloc ieee80211_hw");
		return -ENOMEM;
	}

	priv = hw->priv;
	priv->hw = hw;
	spi_set_drvdata(spi, priv);
	priv->spi = spi;

	spi->bits_per_word = 16;
	spi->max_speed_hz = 24000000;

	ret = spi_setup(spi);
	if (ret < 0) {
		dev_err(&priv->spi->dev, "spi_setup failed");
		goto err_free;
	}

	ret = gpio_request(p54spi_gpio_power, "p54spi power");
	if (ret < 0) {
		dev_err(&priv->spi->dev, "power GPIO request failed: %d", ret);
		goto err_free;
	}

	ret = gpio_request(p54spi_gpio_irq, "p54spi irq");
	if (ret < 0) {
		dev_err(&priv->spi->dev, "irq GPIO request failed: %d", ret);
		goto err_free_gpio_power;
	}

	gpio_direction_output(p54spi_gpio_power, 0);
	gpio_direction_input(p54spi_gpio_irq);

	ret = request_irq(gpio_to_irq(p54spi_gpio_irq),
			  p54spi_interrupt, 0, "p54spi",
			  priv->spi);
	if (ret < 0) {
		dev_err(&priv->spi->dev, "request_irq() failed");
		goto err_free_gpio_irq;
	}

	irq_set_irq_type(gpio_to_irq(p54spi_gpio_irq), IRQ_TYPE_EDGE_RISING);

	disable_irq(gpio_to_irq(p54spi_gpio_irq));

	INIT_WORK(&priv->work, p54spi_work);
	init_completion(&priv->fw_comp);
	INIT_LIST_HEAD(&priv->tx_pending);
	mutex_init(&priv->mutex);
	spin_lock_init(&priv->tx_lock);
	SET_IEEE80211_DEV(hw, &spi->dev);
	priv->common.open = p54spi_op_start;
	priv->common.stop = p54spi_op_stop;
	priv->common.tx = p54spi_op_tx;

	ret = p54spi_request_firmware(hw);
	if (ret < 0)
		goto err_free_common;

	ret = p54spi_request_eeprom(hw);
	if (ret)
		goto err_free_common;

	ret = p54_register_common(hw, &priv->spi->dev);
	if (ret)
		goto err_free_common;

	return 0;

err_free_common:
	free_irq(gpio_to_irq(p54spi_gpio_irq), spi);
err_free_gpio_irq:
	gpio_free(p54spi_gpio_irq);
err_free_gpio_power:
	gpio_free(p54spi_gpio_power);
err_free:
	p54_free_common(priv->hw);
	return ret;
}