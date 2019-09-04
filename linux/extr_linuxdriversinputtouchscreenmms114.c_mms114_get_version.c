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
struct mms114_data {int type; TYPE_1__* client; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMS114_TSP_REV ; 
 int /*<<< orphan*/  MMS152_COMPAT_GROUP ; 
 int /*<<< orphan*/  MMS152_FW_REV ; 
#define  TYPE_MMS114 129 
#define  TYPE_MMS152 128 
 int __mms114_read_reg (struct mms114_data*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int i2c_smbus_read_byte_data (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mms114_get_version(struct mms114_data *data)
{
	struct device *dev = &data->client->dev;
	u8 buf[6];
	int group;
	int error;

	switch (data->type) {
	case TYPE_MMS152:
		error = __mms114_read_reg(data, MMS152_FW_REV, 3, buf);
		if (error)
			return error;

		group = i2c_smbus_read_byte_data(data->client,
						  MMS152_COMPAT_GROUP);
		if (group < 0)
			return group;

		dev_info(dev, "TSP FW Rev: bootloader 0x%x / core 0x%x / config 0x%x, Compat group: %c\n",
			 buf[0], buf[1], buf[2], group);
		break;

	case TYPE_MMS114:
		error = __mms114_read_reg(data, MMS114_TSP_REV, 6, buf);
		if (error)
			return error;

		dev_info(dev, "TSP Rev: 0x%x, HW Rev: 0x%x, Firmware Ver: 0x%x\n",
			 buf[0], buf[1], buf[3]);
		break;
	}

	return 0;
}