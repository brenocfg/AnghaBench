#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  coherent_dma_mask; } ;
struct spi_device {int bits_per_word; int max_speed_hz; TYPE_4__ dev; } ;
struct of_device_id {scalar_t__ data; } ;
struct net_device {int /*<<< orphan*/  flags; int /*<<< orphan*/ * netdev_ops; } ;
struct TYPE_12__ {int freq; } ;
struct TYPE_13__ {int ctrlmode_supported; TYPE_1__ clock; int /*<<< orphan*/  do_set_mode; int /*<<< orphan*/ * bittiming_const; } ;
struct mcp251x_priv {int model; struct clk* power; void* spi_rx_buf; void* spi_tx_buf; scalar_t__ spi_tx_dma; scalar_t__ spi_rx_dma; int /*<<< orphan*/  mcp_lock; struct spi_device* spi; struct clk* transceiver; struct clk* clk; struct net_device* net; TYPE_2__ can; } ;
struct mcp251x_platform_data {int oscillator_frequency; } ;
struct clk {int dummy; } ;
typedef  enum mcp251x_model { ____Placeholder_mcp251x_model } mcp251x_model ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_14__ {int driver_data; } ;

/* Variables and functions */
 int CAN_CTRLMODE_3_SAMPLES ; 
 int CAN_CTRLMODE_LISTENONLY ; 
 int CAN_CTRLMODE_LOOPBACK ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int ERANGE ; 
 int /*<<< orphan*/  GFP_DMA ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IFF_ECHO ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int PAGE_SIZE ; 
 int PTR_ERR (struct clk*) ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,TYPE_4__*) ; 
 int /*<<< orphan*/  SPI_TRANSFER_BUF_LEN ; 
 int /*<<< orphan*/  TX_ECHO_SKB_MAX ; 
 struct net_device* alloc_candev (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (struct clk*) ; 
 int clk_get_rate (struct clk*) ; 
 int clk_prepare_enable (struct clk*) ; 
 int /*<<< orphan*/  dev_err (TYPE_4__*,char*,int) ; 
 struct mcp251x_platform_data* dev_get_platdata (TYPE_4__*) ; 
 int /*<<< orphan*/  devm_can_led_init (struct net_device*) ; 
 struct clk* devm_clk_get (TYPE_4__*,int /*<<< orphan*/ *) ; 
 void* devm_kzalloc (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* devm_regulator_get_optional (TYPE_4__*,char*) ; 
 void* dmam_alloc_coherent (TYPE_4__*,int,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_candev (struct net_device*) ; 
 int /*<<< orphan*/  mcp251x_bittiming_const ; 
 int /*<<< orphan*/  mcp251x_do_set_mode ; 
 scalar_t__ mcp251x_enable_dma ; 
 int mcp251x_hw_probe (struct spi_device*) ; 
 int /*<<< orphan*/  mcp251x_hw_sleep (struct spi_device*) ; 
 scalar_t__ mcp251x_is_2510 (struct spi_device*) ; 
 int /*<<< orphan*/  mcp251x_netdev_ops ; 
 int /*<<< orphan*/  mcp251x_of_match ; 
 int mcp251x_power_enable (struct clk*,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,int) ; 
 struct mcp251x_priv* netdev_priv (struct net_device*) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int register_candev (struct net_device*) ; 
 TYPE_3__* spi_get_device_id (struct spi_device*) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct mcp251x_priv*) ; 
 int spi_setup (struct spi_device*) ; 

__attribute__((used)) static int mcp251x_can_probe(struct spi_device *spi)
{
	const struct of_device_id *of_id = of_match_device(mcp251x_of_match,
							   &spi->dev);
	struct mcp251x_platform_data *pdata = dev_get_platdata(&spi->dev);
	struct net_device *net;
	struct mcp251x_priv *priv;
	struct clk *clk;
	int freq, ret;

	clk = devm_clk_get(&spi->dev, NULL);
	if (IS_ERR(clk)) {
		if (pdata)
			freq = pdata->oscillator_frequency;
		else
			return PTR_ERR(clk);
	} else {
		freq = clk_get_rate(clk);
	}

	/* Sanity check */
	if (freq < 1000000 || freq > 25000000)
		return -ERANGE;

	/* Allocate can/net device */
	net = alloc_candev(sizeof(struct mcp251x_priv), TX_ECHO_SKB_MAX);
	if (!net)
		return -ENOMEM;

	if (!IS_ERR(clk)) {
		ret = clk_prepare_enable(clk);
		if (ret)
			goto out_free;
	}

	net->netdev_ops = &mcp251x_netdev_ops;
	net->flags |= IFF_ECHO;

	priv = netdev_priv(net);
	priv->can.bittiming_const = &mcp251x_bittiming_const;
	priv->can.do_set_mode = mcp251x_do_set_mode;
	priv->can.clock.freq = freq / 2;
	priv->can.ctrlmode_supported = CAN_CTRLMODE_3_SAMPLES |
		CAN_CTRLMODE_LOOPBACK | CAN_CTRLMODE_LISTENONLY;
	if (of_id)
		priv->model = (enum mcp251x_model)of_id->data;
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

	/* If requested, allocate DMA buffers */
	if (mcp251x_enable_dma) {
		spi->dev.coherent_dma_mask = ~0;

		/*
		 * Minimum coherent DMA allocation is PAGE_SIZE, so allocate
		 * that much and share it between Tx and Rx DMA buffers.
		 */
		priv->spi_tx_buf = dmam_alloc_coherent(&spi->dev,
						       PAGE_SIZE,
						       &priv->spi_tx_dma,
						       GFP_DMA);

		if (priv->spi_tx_buf) {
			priv->spi_rx_buf = (priv->spi_tx_buf + (PAGE_SIZE / 2));
			priv->spi_rx_dma = (dma_addr_t)(priv->spi_tx_dma +
							(PAGE_SIZE / 2));
		} else {
			/* Fall back to non-DMA */
			mcp251x_enable_dma = 0;
		}
	}

	/* Allocate non-DMA buffers */
	if (!mcp251x_enable_dma) {
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
	}

	SET_NETDEV_DEV(net, &spi->dev);

	/* Here is OK to not lock the MCP, no one knows about it yet */
	ret = mcp251x_hw_probe(spi);
	if (ret) {
		if (ret == -ENODEV)
			dev_err(&spi->dev, "Cannot initialize MCP%x. Wrong wiring?\n", priv->model);
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
	if (!IS_ERR(clk))
		clk_disable_unprepare(clk);

out_free:
	free_candev(net);

	dev_err(&spi->dev, "Probe failed, err=%d\n", -ret);
	return ret;
}