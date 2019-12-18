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
struct vcnl4000_data {int rev; int al_scale; int /*<<< orphan*/  vcnl4000_lock; TYPE_1__* client; int /*<<< orphan*/  id; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  VCNL4000 ; 
#define  VCNL4000_PROD_ID 129 
 int /*<<< orphan*/  VCNL4000_PROD_REV ; 
 int /*<<< orphan*/  VCNL4010 ; 
#define  VCNL4010_PROD_ID 128 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int i2c_smbus_read_byte_data (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vcnl4000_init(struct vcnl4000_data *data)
{
	int ret, prod_id;

	ret = i2c_smbus_read_byte_data(data->client, VCNL4000_PROD_REV);
	if (ret < 0)
		return ret;

	prod_id = ret >> 4;
	switch (prod_id) {
	case VCNL4000_PROD_ID:
		if (data->id != VCNL4000)
			dev_warn(&data->client->dev,
					"wrong device id, use vcnl4000");
		break;
	case VCNL4010_PROD_ID:
		if (data->id != VCNL4010)
			dev_warn(&data->client->dev,
					"wrong device id, use vcnl4010/4020");
		break;
	default:
		return -ENODEV;
	}

	data->rev = ret & 0xf;
	data->al_scale = 250000;
	mutex_init(&data->vcnl4000_lock);

	return 0;
}