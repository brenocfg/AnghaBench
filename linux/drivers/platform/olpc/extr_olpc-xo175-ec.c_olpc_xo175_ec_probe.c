#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct spi_device {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {int /*<<< orphan*/ * tx_buf; int /*<<< orphan*/ * rx_buf; } ;
struct olpc_xo175_ec {int /*<<< orphan*/  tx_buf; TYPE_2__ xfer; int /*<<< orphan*/  rx_buf; TYPE_3__* pwrbtn; scalar_t__ logbuf_len; int /*<<< orphan*/  cmd_done; int /*<<< orphan*/  cmd_state; int /*<<< orphan*/  cmd_state_lock; struct spi_device* spi; int /*<<< orphan*/  gpio_cmd; } ;
struct TYPE_6__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_8__ {char* name; TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_STATE_IDLE ; 
 int EBUSY ; 
 int /*<<< orphan*/  EC_ALL_EVENTS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KEY_POWER ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_gpiod_get (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 TYPE_3__* devm_input_allocate_device (int /*<<< orphan*/ *) ; 
 struct olpc_xo175_ec* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int input_register_device (TYPE_3__*) ; 
 int /*<<< orphan*/  input_set_capability (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ olpc_ec ; 
 int /*<<< orphan*/  olpc_ec_driver_register (int /*<<< orphan*/ *,struct olpc_xo175_ec*) ; 
 int /*<<< orphan*/  olpc_xo175_ec_driver ; 
 int /*<<< orphan*/ * olpc_xo175_ec_power_off ; 
 int /*<<< orphan*/  olpc_xo175_ec_read_packet (struct olpc_xo175_ec*) ; 
 int /*<<< orphan*/  olpc_xo175_ec_set_event_mask (int /*<<< orphan*/ ) ; 
 scalar_t__ platform_device_register_resndata (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pm_power_off ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct olpc_xo175_ec*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int olpc_xo175_ec_probe(struct spi_device *spi)
{
	struct olpc_xo175_ec *priv;
	int ret;

	if (olpc_ec) {
		dev_err(&spi->dev, "OLPC EC already registered.\n");
		return -EBUSY;
	}

	priv = devm_kzalloc(&spi->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->gpio_cmd = devm_gpiod_get(&spi->dev, "cmd", GPIOD_OUT_LOW);
	if (IS_ERR(priv->gpio_cmd)) {
		dev_err(&spi->dev, "failed to get cmd gpio: %ld\n",
					PTR_ERR(priv->gpio_cmd));
		return PTR_ERR(priv->gpio_cmd);
	}

	priv->spi = spi;

	spin_lock_init(&priv->cmd_state_lock);
	priv->cmd_state = CMD_STATE_IDLE;
	init_completion(&priv->cmd_done);

	priv->logbuf_len = 0;

	/* Set up power button input device */
	priv->pwrbtn = devm_input_allocate_device(&spi->dev);
	if (!priv->pwrbtn)
		return -ENOMEM;
	priv->pwrbtn->name = "Power Button";
	priv->pwrbtn->dev.parent = &spi->dev;
	input_set_capability(priv->pwrbtn, EV_KEY, KEY_POWER);
	ret = input_register_device(priv->pwrbtn);
	if (ret) {
		dev_err(&spi->dev, "error registering input device: %d\n", ret);
		return ret;
	}

	spi_set_drvdata(spi, priv);

	priv->xfer.rx_buf = &priv->rx_buf;
	priv->xfer.tx_buf = &priv->tx_buf;

	olpc_xo175_ec_read_packet(priv);

	olpc_ec_driver_register(&olpc_xo175_ec_driver, priv);
	olpc_ec = platform_device_register_resndata(&spi->dev, "olpc-ec", -1,
							NULL, 0, NULL, 0);

	/* Enable all EC events while we're awake */
	olpc_xo175_ec_set_event_mask(EC_ALL_EVENTS);

	if (pm_power_off == NULL)
		pm_power_off = olpc_xo175_ec_power_off;

	dev_info(&spi->dev, "OLPC XO-1.75 Embedded Controller driver\n");

	return 0;
}