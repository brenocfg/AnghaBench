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
struct TYPE_6__ {int /*<<< orphan*/  lock; void* last_measurement; void* sampling_rate; int /*<<< orphan*/  reg; } ;
struct TYPE_5__ {int /*<<< orphan*/  lock; void* last_measurement; void* sampling_rate; int /*<<< orphan*/  reg; } ;
struct vcnl4000_data {int rev; int al_scale; TYPE_2__ vcnl4200_ps; TYPE_1__ vcnl4200_al; TYPE_3__* client; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  VCNL4040_DEV_ID ; 
#define  VCNL4040_PROD_ID 129 
 int /*<<< orphan*/  VCNL4200_AL_CONF ; 
 int /*<<< orphan*/  VCNL4200_AL_DATA ; 
 int /*<<< orphan*/  VCNL4200_DEV_ID ; 
#define  VCNL4200_PROD_ID 128 
 int /*<<< orphan*/  VCNL4200_PS_CONF1 ; 
 int /*<<< orphan*/  VCNL4200_PS_DATA ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int i2c_smbus_read_word_data (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_write_word_data (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* ktime_set (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vcnl4200_init(struct vcnl4000_data *data)
{
	int ret, id;

	ret = i2c_smbus_read_word_data(data->client, VCNL4200_DEV_ID);
	if (ret < 0)
		return ret;

	id = ret & 0xff;

	if (id != VCNL4200_PROD_ID) {
		ret = i2c_smbus_read_word_data(data->client, VCNL4040_DEV_ID);
		if (ret < 0)
			return ret;

		id = ret & 0xff;

		if (id != VCNL4040_PROD_ID)
			return -ENODEV;
	}

	dev_dbg(&data->client->dev, "device id 0x%x", id);

	data->rev = (ret >> 8) & 0xf;

	/* Set defaults and enable both channels */
	ret = i2c_smbus_write_word_data(data->client, VCNL4200_AL_CONF, 0);
	if (ret < 0)
		return ret;
	ret = i2c_smbus_write_word_data(data->client, VCNL4200_PS_CONF1, 0);
	if (ret < 0)
		return ret;

	data->al_scale = 24000;
	data->vcnl4200_al.reg = VCNL4200_AL_DATA;
	data->vcnl4200_ps.reg = VCNL4200_PS_DATA;
	switch (id) {
	case VCNL4200_PROD_ID:
		/* Integration time is 50ms, but the experiments */
		/* show 54ms in total. */
		data->vcnl4200_al.sampling_rate = ktime_set(0, 54000 * 1000);
		data->vcnl4200_ps.sampling_rate = ktime_set(0, 4200 * 1000);
		break;
	case VCNL4040_PROD_ID:
		/* Integration time is 80ms, add 10ms. */
		data->vcnl4200_al.sampling_rate = ktime_set(0, 100000 * 1000);
		data->vcnl4200_ps.sampling_rate = ktime_set(0, 100000 * 1000);
		break;
	}
	data->vcnl4200_al.last_measurement = ktime_set(0, 0);
	data->vcnl4200_ps.last_measurement = ktime_set(0, 0);
	mutex_init(&data->vcnl4200_al.lock);
	mutex_init(&data->vcnl4200_ps.lock);

	return 0;
}