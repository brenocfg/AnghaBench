#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct spi_device {int bits_per_word; int /*<<< orphan*/  dev; } ;
struct of_device_id {scalar_t__ data; } ;
struct net_device {int /*<<< orphan*/  flags; int /*<<< orphan*/ * netdev_ops; } ;
struct TYPE_4__ {int freq; } ;
struct TYPE_5__ {int ctrlmode_supported; TYPE_1__ clock; int /*<<< orphan*/  do_get_berr_counter; int /*<<< orphan*/  do_set_mode; int /*<<< orphan*/ * bittiming_const; } ;
struct hi3110_priv {int model; struct clk* power; void* spi_rx_buf; void* spi_tx_buf; int /*<<< orphan*/  hi3110_lock; struct spi_device* spi; struct clk* transceiver; struct clk* clk; struct net_device* net; TYPE_2__ can; } ;
struct clk {int dummy; } ;
typedef  enum hi3110_model { ____Placeholder_hi3110_model } hi3110_model ;
struct TYPE_6__ {int driver_data; } ;

/* Variables and functions */
 int CAN_CTRLMODE_3_SAMPLES ; 
 int CAN_CTRLMODE_BERR_REPORTING ; 
 int CAN_CTRLMODE_LISTENONLY ; 
 int CAN_CTRLMODE_LOOPBACK ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int ERANGE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HI3110_RX_BUF_LEN ; 
 int /*<<< orphan*/  HI3110_TX_ECHO_SKB_MAX ; 
 int /*<<< orphan*/  IFF_ECHO ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int PTR_ERR (struct clk*) ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ *) ; 
 struct net_device* alloc_candev (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (struct clk*) ; 
 int clk_get_rate (struct clk*) ; 
 int clk_prepare_enable (struct clk*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  devm_can_led_init (struct net_device*) ; 
 struct clk* devm_clk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* devm_kzalloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* devm_regulator_get_optional (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  free_candev (struct net_device*) ; 
 int /*<<< orphan*/  hi3110_bittiming_const ; 
 int /*<<< orphan*/  hi3110_do_set_mode ; 
 int /*<<< orphan*/  hi3110_get_berr_counter ; 
 int hi3110_hw_probe (struct spi_device*) ; 
 int /*<<< orphan*/  hi3110_hw_sleep (struct spi_device*) ; 
 int /*<<< orphan*/  hi3110_netdev_ops ; 
 int /*<<< orphan*/  hi3110_of_match ; 
 int hi3110_power_enable (struct clk*,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,int) ; 
 struct hi3110_priv* netdev_priv (struct net_device*) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int register_candev (struct net_device*) ; 
 TYPE_3__* spi_get_device_id (struct spi_device*) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct hi3110_priv*) ; 
 int spi_setup (struct spi_device*) ; 

__attribute__((used)) static int hi3110_can_probe(struct spi_device *spi)
{
	const struct of_device_id *of_id = of_match_device(hi3110_of_match,
							   &spi->dev);
	struct net_device *net;
	struct hi3110_priv *priv;
	struct clk *clk;
	int freq, ret;

	clk = devm_clk_get(&spi->dev, NULL);
	if (IS_ERR(clk)) {
		dev_err(&spi->dev, "no CAN clock source defined\n");
		return PTR_ERR(clk);
	}
	freq = clk_get_rate(clk);

	/* Sanity check */
	if (freq > 40000000)
		return -ERANGE;

	/* Allocate can/net device */
	net = alloc_candev(sizeof(struct hi3110_priv), HI3110_TX_ECHO_SKB_MAX);
	if (!net)
		return -ENOMEM;

	if (!IS_ERR(clk)) {
		ret = clk_prepare_enable(clk);
		if (ret)
			goto out_free;
	}

	net->netdev_ops = &hi3110_netdev_ops;
	net->flags |= IFF_ECHO;

	priv = netdev_priv(net);
	priv->can.bittiming_const = &hi3110_bittiming_const;
	priv->can.do_set_mode = hi3110_do_set_mode;
	priv->can.do_get_berr_counter = hi3110_get_berr_counter;
	priv->can.clock.freq = freq / 2;
	priv->can.ctrlmode_supported = CAN_CTRLMODE_3_SAMPLES |
		CAN_CTRLMODE_LOOPBACK |
		CAN_CTRLMODE_LISTENONLY |
		CAN_CTRLMODE_BERR_REPORTING;

	if (of_id)
		priv->model = (enum hi3110_model)of_id->data;
	else
		priv->model = spi_get_device_id(spi)->driver_data;
	priv->net = net;
	priv->clk = clk;

	spi_set_drvdata(spi, priv);

	/* Configure the SPI bus */
	spi->bits_per_word = 8;
	ret = spi_setup(spi);
	if (ret)
		goto out_clk;

	priv->power = devm_regulator_get_optional(&spi->dev, "vdd");
	priv->transceiver = devm_regulator_get_optional(&spi->dev, "xceiver");
	if ((PTR_ERR(priv->power) == -EPROBE_DEFER) ||
	    (PTR_ERR(priv->transceiver) == -EPROBE_DEFER)) {
		ret = -EPROBE_DEFER;
		goto out_clk;
	}

	ret = hi3110_power_enable(priv->power, 1);
	if (ret)
		goto out_clk;

	priv->spi = spi;
	mutex_init(&priv->hi3110_lock);

	priv->spi_tx_buf = devm_kzalloc(&spi->dev, HI3110_RX_BUF_LEN,
					GFP_KERNEL);
	if (!priv->spi_tx_buf) {
		ret = -ENOMEM;
		goto error_probe;
	}
	priv->spi_rx_buf = devm_kzalloc(&spi->dev, HI3110_RX_BUF_LEN,
					GFP_KERNEL);

	if (!priv->spi_rx_buf) {
		ret = -ENOMEM;
		goto error_probe;
	}

	SET_NETDEV_DEV(net, &spi->dev);

	ret = hi3110_hw_probe(spi);
	if (ret) {
		if (ret == -ENODEV)
			dev_err(&spi->dev, "Cannot initialize %x. Wrong wiring?\n",
				priv->model);
		goto error_probe;
	}
	hi3110_hw_sleep(spi);

	ret = register_candev(net);
	if (ret)
		goto error_probe;

	devm_can_led_init(net);
	netdev_info(net, "%x successfully initialized.\n", priv->model);

	return 0;

 error_probe:
	hi3110_power_enable(priv->power, 0);

 out_clk:
	if (!IS_ERR(clk))
		clk_disable_unprepare(clk);

 out_free:
	free_candev(net);

	dev_err(&spi->dev, "Probe failed, err=%d\n", -ret);
	return ret;
}