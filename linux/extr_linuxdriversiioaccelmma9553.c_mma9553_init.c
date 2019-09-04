#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_7__ {void* config; int /*<<< orphan*/  sleepthd; int /*<<< orphan*/  sleepmax; int /*<<< orphan*/  sleepmin; } ;
struct mma9553_data {TYPE_2__* client; TYPE_1__ conf; int /*<<< orphan*/  gpio_bitnum; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMA9551_APPID_PEDOMETER ; 
 int /*<<< orphan*/  MMA9551_RSC_PED ; 
 int /*<<< orphan*/  MMA9553_DEFAULT_SLEEPMAX ; 
 int /*<<< orphan*/  MMA9553_DEFAULT_SLEEPMIN ; 
 int /*<<< orphan*/  MMA9553_DEFAULT_SLEEPTHD ; 
 int /*<<< orphan*/  MMA9553_MASK_CONF_ACT_DBCNTM ; 
 int /*<<< orphan*/  MMA9553_MASK_CONF_CONFIG ; 
 int /*<<< orphan*/  MMA9553_MAX_BITNUM ; 
 int /*<<< orphan*/  MMA9553_REG_CONF_SLEEPMIN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int mma9551_app_reset (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int mma9551_read_config_words (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int mma9551_read_version (TYPE_2__*) ; 
 int mma9551_set_device_state (TYPE_2__*,int) ; 
 int mma9551_write_config_words (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int mma9553_conf_gpio (struct mma9553_data*) ; 
 void* mma9553_set_bits (void*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mma9553_init(struct mma9553_data *data)
{
	int ret;

	ret = mma9551_read_version(data->client);
	if (ret)
		return ret;

	/*
	 * Read all the pedometer configuration registers. This is used as
	 * a device identification command to differentiate the MMA9553L
	 * from the MMA9550L.
	 */
	ret = mma9551_read_config_words(data->client, MMA9551_APPID_PEDOMETER,
					MMA9553_REG_CONF_SLEEPMIN,
					sizeof(data->conf) / sizeof(u16),
					(u16 *)&data->conf);
	if (ret < 0) {
		dev_err(&data->client->dev,
			"failed to read configuration registers\n");
		return ret;
	}

	/* Reset GPIO */
	data->gpio_bitnum = MMA9553_MAX_BITNUM;
	ret = mma9553_conf_gpio(data);
	if (ret < 0)
		return ret;

	ret = mma9551_app_reset(data->client, MMA9551_RSC_PED);
	if (ret < 0)
		return ret;

	/* Init config registers */
	data->conf.sleepmin = MMA9553_DEFAULT_SLEEPMIN;
	data->conf.sleepmax = MMA9553_DEFAULT_SLEEPMAX;
	data->conf.sleepthd = MMA9553_DEFAULT_SLEEPTHD;
	data->conf.config = mma9553_set_bits(data->conf.config, 1,
					     MMA9553_MASK_CONF_CONFIG);
	/*
	 * Clear the activity debounce counter when the activity level changes,
	 * so that the confidence level applies for any activity level.
	 */
	data->conf.config = mma9553_set_bits(data->conf.config, 1,
					     MMA9553_MASK_CONF_ACT_DBCNTM);
	ret = mma9551_write_config_words(data->client, MMA9551_APPID_PEDOMETER,
					 MMA9553_REG_CONF_SLEEPMIN,
					 sizeof(data->conf) / sizeof(u16),
					 (u16 *)&data->conf);
	if (ret < 0) {
		dev_err(&data->client->dev,
			"failed to write configuration registers\n");
		return ret;
	}

	return mma9551_set_device_state(data->client, true);
}