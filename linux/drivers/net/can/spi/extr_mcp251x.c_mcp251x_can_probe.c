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
struct spi_device {int bits_per_word; int max_speed_hz; int /*<<< orphan*/  dev; } ;
struct net_device {int /*<<< orphan*/  flags; int /*<<< orphan*/ * netdev_ops; } ;
struct TYPE_4__ {int freq; } ;
struct TYPE_5__ {int ctrlmode_supported; TYPE_1__ clock; int /*<<< orphan*/  do_set_mode; int /*<<< orphan*/ * bittiming_const; } ;
struct mcp251x_priv {int model; struct clk* power; void* spi_rx_buf; void* spi_tx_buf; int /*<<< orphan*/  mcp_lock; struct spi_device* spi; struct clk* transceiver; struct clk* clk; struct net_device* net; TYPE_2__ can; } ;
struct mcp251x_platform_data {int oscillator_frequency; } ;
struct clk {int dummy; } ;
typedef  enum mcp251x_model { ____Placeholder_mcp251x_model } mcp251x_model ;
struct TYPE_6__ {int driver_data; } ;

/* Variables and functions */
 int CAN_CTRLMODE_3_SAMPLES ; 
 int CAN_CTRLMODE_LISTENONLY ; 
 int CAN_CTRLMODE_LOOPBACK ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int ERANGE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IFF_ECHO ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int PTR_ERR (struct clk*) ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SPI_TRANSFER_BUF_LEN ; 
 int /*<<< orphan*/  TX_ECHO_SKB_MAX ; 
 struct net_device* alloc_candev (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (struct clk*) ; 
 int clk_get_rate (struct clk*) ; 
 int clk_prepare_enable (struct clk*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct mcp251x_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 void* device_get_match_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_can_led_init (struct net_device*) ; 
 struct clk* devm_clk_get_optional (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* devm_kzalloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* devm_regulator_get_optional (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  free_candev (struct net_device*) ; 
 int /*<<< orphan*/  mcp251x_bittiming_const ; 
 int /*<<< orphan*/  mcp251x_do_set_mode ; 
 int mcp251x_hw_probe (struct spi_device*) ; 
 int /*<<< orphan*/  mcp251x_hw_sleep (struct spi_device*) ; 
 scalar_t__ mcp251x_is_2510 (struct spi_device*) ; 
 int /*<<< orphan*/  mcp251x_netdev_ops ; 
 int mcp251x_power_enable (struct clk*,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,int) ; 
 struct mcp251x_priv* netdev_priv (struct net_device*) ; 
 int register_candev (struct net_device*) ; 
 TYPE_3__* spi_get_device_id (struct spi_device*) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct mcp251x_priv*) ; 
 int spi_setup (struct spi_device*) ; 

__attribute__((used)) static int mcp251x_can_probe(struct spi_device *spi)
{
	const void *match = device_get_match_data(&spi->dev);
	struct mcp251x_platform_data *pdata = dev_get_platdata(&spi->dev);
	struct net_device *net;
	struct mcp251x_priv *priv;
	struct clk *clk;
	int freq, ret;

	clk = devm_clk_get_optional(&spi->dev, NULL);
	if (IS_ERR(clk))
		return PTR_ERR(clk);

	freq = clk_get_rate(clk);
	if (freq == 0 && pdata)
		freq = pdata->oscillator_frequency;

	/* Sanity check */
	if (freq < 1000000 || freq > 25000000)
		return -ERANGE;

	/* Allocate can/net device */
	net = alloc_candev(sizeof(struct mcp251x_priv), TX_ECHO_SKB_MAX);
	if (!net)
		return -ENOMEM;

	ret = clk_prepare_enable(clk);
	if (ret)
		goto out_free;

	net->netdev_ops = &mcp251x_netdev_ops;
	net->flags |= IFF_ECHO;

	priv = netdev_priv(net);
	priv->can.bittiming_const = &mcp251x_bittiming_const;
	priv->can.do_set_mode = mcp251x_do_set_mode;
	priv->can.clock.freq = freq / 2;
	priv->can.ctrlmode_supported = CAN_CTRLMODE_3_SAMPLES |
		CAN_CTRLMODE_LOOPBACK | CAN_CTRLMODE_LISTENONLY;
	if (match)
		priv->model = (enum mcp251x_model)match;
	else
		priv->model = spi_get_device_id(spi)->driver_data;
	priv->net = net;
	priv->clk = clk;

	spi_set_drvdata(spi, priv);

	/* Configure the SPI bus */
	spi->bits_per_word = 8;
	if (mcp251x_is_2510(spi))
		spi->max_speed_hz = spi->max_speed_hz ? : 5 * 1000 * 1000;
	else
		spi->max_speed_hz = spi->max_speed_hz ? : 10 * 1000 * 1000;
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

	ret = mcp251x_power_enable(priv->power, 1);
	if (ret)
		goto out_clk;

	priv->spi = spi;
	mutex_init(&priv->mcp_lock);

	priv->spi_tx_buf = devm_kzalloc(&spi->dev, SPI_TRANSFER_BUF_LEN,
					GFP_KERNEL);
	if (!priv->spi_tx_buf) {
		ret = -ENOMEM;
		goto error_probe;
	}

	priv->spi_rx_buf = devm_kzalloc(&spi->dev, SPI_TRANSFER_BUF_LEN,
					GFP_KERNEL);
	if (!priv->spi_rx_buf) {
		ret = -ENOMEM;
		goto error_probe;
	}

	SET_NETDEV_DEV(net, &spi->dev);

	/* Here is OK to not lock the MCP, no one knows about it yet */
	ret = mcp251x_hw_probe(spi);
	if (ret) {
		if (ret == -ENODEV)
			dev_err(&spi->dev, "Cannot initialize MCP%x. Wrong wiring?\n",
				priv->model);
		goto error_probe;
	}

	mcp251x_hw_sleep(spi);

	ret = register_candev(net);
	if (ret)
		goto error_probe;

	devm_can_led_init(net);

	netdev_info(net, "MCP%x successfully initialized.\n", priv->model);
	return 0;

error_probe:
	mcp251x_power_enable(priv->power, 0);

out_clk:
	clk_disable_unprepare(clk);

out_free:
	free_candev(net);

	dev_err(&spi->dev, "Probe failed, err=%d\n", -ret);
	return ret;
}