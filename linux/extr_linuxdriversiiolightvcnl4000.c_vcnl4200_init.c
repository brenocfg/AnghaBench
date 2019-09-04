#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  lock; void* last_measurement; void* sampling_rate; int /*<<< orphan*/  reg; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; void* last_measurement; void* sampling_rate; int /*<<< orphan*/  reg; } ;
struct vcnl4000_data {int rev; int al_scale; TYPE_2__ vcnl4200_ps; TYPE_1__ vcnl4200_al; int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  VCNL4200_AL_CONF ; 
 int /*<<< orphan*/  VCNL4200_AL_DATA ; 
 int /*<<< orphan*/  VCNL4200_DEV_ID ; 
 int VCNL4200_PROD_ID ; 
 int /*<<< orphan*/  VCNL4200_PS_CONF1 ; 
 int /*<<< orphan*/  VCNL4200_PS_DATA ; 
 int i2c_smbus_read_word_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 void* ktime_set (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vcnl4200_init(struct vcnl4000_data *data)
{
	int ret;

	ret = i2c_smbus_read_word_data(data->client, VCNL4200_DEV_ID);
	if (ret < 0)
		return ret;

	if ((ret & 0xff) != VCNL4200_PROD_ID)
		return -ENODEV;

	data->rev = (ret >> 8) & 0xf;

	/* Set defaults and enable both channels */
	ret = i2c_smbus_write_byte_data(data->client, VCNL4200_AL_CONF, 0x00);
	if (ret < 0)
		return ret;
	ret = i2c_smbus_write_byte_data(data->client, VCNL4200_PS_CONF1, 0x00);
	if (ret < 0)
		return ret;

	data->al_scale = 24000;
	data->vcnl4200_al.reg = VCNL4200_AL_DATA;
	data->vcnl4200_ps.reg = VCNL4200_PS_DATA;
	/* Integration time is 50ms, but the experiments show 54ms in total. */
	data->vcnl4200_al.sampling_rate = ktime_set(0, 54000 * 1000);
	data->vcnl4200_ps.sampling_rate = ktime_set(0, 4200 * 1000);
	data->vcnl4200_al.last_measurement = ktime_set(0, 0);
	data->vcnl4200_ps.last_measurement = ktime_set(0, 0);
	mutex_init(&data->vcnl4200_al.lock);
	mutex_init(&data->vcnl4200_ps.lock);

	return 0;
}