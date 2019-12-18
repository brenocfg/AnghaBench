#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct v4l2_rds_data {int dummy; } ;
struct si476x_platform_data {int gpio_reset; int /*<<< orphan*/  pinmux; int /*<<< orphan*/  diversity_mode; int /*<<< orphan*/  power_up_parameters; } ;
struct si476x_pinmux {int dummy; } ;
struct TYPE_6__ {scalar_t__ dclk; scalar_t__ dfs; scalar_t__ dout; scalar_t__ xout; } ;
struct si476x_core {int gpio_reset; int rds_fifo_depth; scalar_t__ chip_id; int /*<<< orphan*/  rds_fifo; struct mfd_cell* cells; TYPE_2__ pinmux; int /*<<< orphan*/  status_monitor; int /*<<< orphan*/  rds_fifo_drainer; int /*<<< orphan*/  rds_read_queue; int /*<<< orphan*/  rds_drainer_status_lock; int /*<<< orphan*/  tuning; int /*<<< orphan*/  command; int /*<<< orphan*/  cmd_lock; TYPE_3__* supplies; int /*<<< orphan*/  diversity_mode; TYPE_2__ power_up_parameters; int /*<<< orphan*/  power_state; int /*<<< orphan*/  is_alive; int /*<<< orphan*/  regmap; struct i2c_client* client; } ;
struct mfd_cell {char* name; } ;
struct i2c_device_id {scalar_t__ driver_data; } ;
struct i2c_client {int irq; scalar_t__ addr; TYPE_1__* adapter; int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;
struct TYPE_7__ {char* supply; } ;
struct TYPE_5__ {int nr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (TYPE_3__*) ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_FALLING ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SI476X_CHIP_SI4761 ; 
 scalar_t__ SI476X_CHIP_SI4764 ; 
 size_t SI476X_CODEC_CELL ; 
 scalar_t__ SI476X_DCLK_DAUDIO ; 
 scalar_t__ SI476X_DFS_DAUDIO ; 
 scalar_t__ SI476X_DOUT_I2S_OUTPUT ; 
 int SI476X_DRIVER_RDS_FIFO_DEPTH ; 
 int /*<<< orphan*/  SI476X_POWER_DOWN ; 
 size_t SI476X_RADIO_CELL ; 
 scalar_t__ SI476X_XOUT_TRISTATE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct si476x_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 struct si476x_core* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_si476x (struct si476x_core*) ; 
 int devm_regulator_bulk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct si476x_core*) ; 
 int /*<<< orphan*/  disable_irq (int) ; 
 int /*<<< orphan*/  gpio_direction_output (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_free (int) ; 
 scalar_t__ gpio_is_valid (int) ; 
 int gpio_request (int,char*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct si476x_core*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int kfifo_alloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfifo_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int mfd_add_devices (int /*<<< orphan*/ *,scalar_t__,struct mfd_cell*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  si476x_core_drain_rds_fifo ; 
 int si476x_core_get_revision_info (struct si476x_core*) ; 
 int /*<<< orphan*/  si476x_core_interrupt ; 
 int /*<<< orphan*/  si476x_core_poll_loop ; 

__attribute__((used)) static int si476x_core_probe(struct i2c_client *client,
			     const struct i2c_device_id *id)
{
	int rval;
	struct si476x_core          *core;
	struct si476x_platform_data *pdata;
	struct mfd_cell *cell;
	int              cell_num;

	core = devm_kzalloc(&client->dev, sizeof(*core), GFP_KERNEL);
	if (!core)
		return -ENOMEM;

	core->client = client;

	core->regmap = devm_regmap_init_si476x(core);
	if (IS_ERR(core->regmap)) {
		rval = PTR_ERR(core->regmap);
		dev_err(&client->dev,
			"Failed to allocate register map: %d\n",
			rval);
		return rval;
	}

	i2c_set_clientdata(client, core);

	atomic_set(&core->is_alive, 0);
	core->power_state = SI476X_POWER_DOWN;

	pdata = dev_get_platdata(&client->dev);
	if (pdata) {
		memcpy(&core->power_up_parameters,
		       &pdata->power_up_parameters,
		       sizeof(core->power_up_parameters));

		core->gpio_reset = -1;
		if (gpio_is_valid(pdata->gpio_reset)) {
			rval = gpio_request(pdata->gpio_reset, "si476x reset");
			if (rval) {
				dev_err(&client->dev,
					"Failed to request gpio: %d\n", rval);
				return rval;
			}
			core->gpio_reset = pdata->gpio_reset;
			gpio_direction_output(core->gpio_reset, 0);
		}

		core->diversity_mode = pdata->diversity_mode;
		memcpy(&core->pinmux, &pdata->pinmux,
		       sizeof(struct si476x_pinmux));
	} else {
		dev_err(&client->dev, "No platform data provided\n");
		return -EINVAL;
	}

	core->supplies[0].supply = "vd";
	core->supplies[1].supply = "va";
	core->supplies[2].supply = "vio1";
	core->supplies[3].supply = "vio2";

	rval = devm_regulator_bulk_get(&client->dev,
				       ARRAY_SIZE(core->supplies),
				       core->supplies);
	if (rval) {
		dev_err(&client->dev, "Failed to get all of the regulators\n");
		goto free_gpio;
	}

	mutex_init(&core->cmd_lock);
	init_waitqueue_head(&core->command);
	init_waitqueue_head(&core->tuning);

	rval = kfifo_alloc(&core->rds_fifo,
			   SI476X_DRIVER_RDS_FIFO_DEPTH *
			   sizeof(struct v4l2_rds_data),
			   GFP_KERNEL);
	if (rval) {
		dev_err(&client->dev, "Could not allocate the FIFO\n");
		goto free_gpio;
	}
	mutex_init(&core->rds_drainer_status_lock);
	init_waitqueue_head(&core->rds_read_queue);
	INIT_WORK(&core->rds_fifo_drainer, si476x_core_drain_rds_fifo);

	if (client->irq) {
		rval = devm_request_threaded_irq(&client->dev,
						 client->irq, NULL,
						 si476x_core_interrupt,
						 IRQF_TRIGGER_FALLING |
						 IRQF_ONESHOT,
						 client->name, core);
		if (rval < 0) {
			dev_err(&client->dev, "Could not request IRQ %d\n",
				client->irq);
			goto free_kfifo;
		}
		disable_irq(client->irq);
		dev_dbg(&client->dev, "IRQ requested.\n");

		core->rds_fifo_depth = 20;
	} else {
		INIT_DELAYED_WORK(&core->status_monitor,
				  si476x_core_poll_loop);
		dev_info(&client->dev,
			 "No IRQ number specified, will use polling\n");

		core->rds_fifo_depth = 5;
	}

	core->chip_id = id->driver_data;

	rval = si476x_core_get_revision_info(core);
	if (rval < 0) {
		rval = -ENODEV;
		goto free_kfifo;
	}

	cell_num = 0;

	cell = &core->cells[SI476X_RADIO_CELL];
	cell->name = "si476x-radio";
	cell_num++;

#ifdef CONFIG_SND_SOC_SI476X
	if ((core->chip_id == SI476X_CHIP_SI4761 ||
	     core->chip_id == SI476X_CHIP_SI4764)	&&
	    core->pinmux.dclk == SI476X_DCLK_DAUDIO     &&
	    core->pinmux.dfs  == SI476X_DFS_DAUDIO      &&
	    core->pinmux.dout == SI476X_DOUT_I2S_OUTPUT &&
	    core->pinmux.xout == SI476X_XOUT_TRISTATE) {
		cell = &core->cells[SI476X_CODEC_CELL];
		cell->name          = "si476x-codec";
		cell_num++;
	}
#endif
	rval = mfd_add_devices(&client->dev,
			       (client->adapter->nr << 8) + client->addr,
			       core->cells, cell_num,
			       NULL, 0, NULL);
	if (!rval)
		return 0;

free_kfifo:
	kfifo_free(&core->rds_fifo);

free_gpio:
	if (gpio_is_valid(core->gpio_reset))
		gpio_free(core->gpio_reset);

	return rval;
}