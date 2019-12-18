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
typedef  int /*<<< orphan*/  u8 ;
struct sps30_state {int /*<<< orphan*/  lock; int /*<<< orphan*/  state; struct i2c_client* client; } ;
struct TYPE_2__ {int /*<<< orphan*/ * parent; } ;
struct iio_dev {int /*<<< orphan*/  available_scan_masks; int /*<<< orphan*/  modes; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/  name; int /*<<< orphan*/ * info; TYPE_1__ dev; } ;
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  name; int /*<<< orphan*/  adapter; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  I2C_FUNC_I2C ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int /*<<< orphan*/  RESET ; 
 int /*<<< orphan*/  SPS30_CRC8_POLYNOMIAL ; 
 int /*<<< orphan*/  SPS30_READ_SERIAL ; 
 int /*<<< orphan*/  crc8_populate_msb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int devm_add_action_or_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sps30_state*) ; 
 struct iio_dev* devm_iio_device_alloc (int /*<<< orphan*/ *,int) ; 
 int devm_iio_device_register (int /*<<< orphan*/ *,struct iio_dev*) ; 
 int devm_iio_triggered_buffer_setup (int /*<<< orphan*/ *,struct iio_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct iio_dev*) ; 
 struct sps30_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sps30_channels ; 
 int /*<<< orphan*/  sps30_crc8_table ; 
 int sps30_do_cmd (struct sps30_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int sps30_do_cmd_reset (struct sps30_state*) ; 
 int /*<<< orphan*/  sps30_info ; 
 int /*<<< orphan*/  sps30_scan_masks ; 
 int /*<<< orphan*/  sps30_stop_meas ; 
 int /*<<< orphan*/  sps30_trigger_handler ; 

__attribute__((used)) static int sps30_probe(struct i2c_client *client)
{
	struct iio_dev *indio_dev;
	struct sps30_state *state;
	u8 buf[32];
	int ret;

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C))
		return -EOPNOTSUPP;

	indio_dev = devm_iio_device_alloc(&client->dev, sizeof(*state));
	if (!indio_dev)
		return -ENOMEM;

	state = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	state->client = client;
	state->state = RESET;
	indio_dev->dev.parent = &client->dev;
	indio_dev->info = &sps30_info;
	indio_dev->name = client->name;
	indio_dev->channels = sps30_channels;
	indio_dev->num_channels = ARRAY_SIZE(sps30_channels);
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->available_scan_masks = sps30_scan_masks;

	mutex_init(&state->lock);
	crc8_populate_msb(sps30_crc8_table, SPS30_CRC8_POLYNOMIAL);

	ret = sps30_do_cmd_reset(state);
	if (ret) {
		dev_err(&client->dev, "failed to reset device\n");
		return ret;
	}

	ret = sps30_do_cmd(state, SPS30_READ_SERIAL, buf, sizeof(buf));
	if (ret) {
		dev_err(&client->dev, "failed to read serial number\n");
		return ret;
	}
	/* returned serial number is already NUL terminated */
	dev_info(&client->dev, "serial number: %s\n", buf);

	ret = devm_add_action_or_reset(&client->dev, sps30_stop_meas, state);
	if (ret)
		return ret;

	ret = devm_iio_triggered_buffer_setup(&client->dev, indio_dev, NULL,
					      sps30_trigger_handler, NULL);
	if (ret)
		return ret;

	return devm_iio_device_register(&client->dev, indio_dev);
}