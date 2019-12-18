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
struct device {int dummy; } ;
struct cyapa_reg_data {int device_status; int finger_btn; } ;
struct cyapa {TYPE_1__* client; } ;
typedef  int /*<<< orphan*/  data ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CYAPA_CMD_GROUP_DATA ; 
 int CYAPA_DEV_NORMAL ; 
 int EINVAL ; 
 int OP_DATA_VALID ; 
 int OP_STATUS_DEV ; 
 int OP_STATUS_SRC ; 
 int cyapa_gen3_event_process (struct cyapa*,struct cyapa_reg_data*) ; 
 int cyapa_read_block (struct cyapa*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,...) ; 

__attribute__((used)) static int cyapa_gen3_irq_handler(struct cyapa *cyapa)
{
	struct device *dev = &cyapa->client->dev;
	struct cyapa_reg_data data;
	int ret;

	ret = cyapa_read_block(cyapa, CYAPA_CMD_GROUP_DATA, (u8 *)&data);
	if (ret != sizeof(data)) {
		dev_err(dev, "failed to read report data, (%d)\n", ret);
		return -EINVAL;
	}

	if ((data.device_status & OP_STATUS_SRC) != OP_STATUS_SRC ||
	    (data.device_status & OP_STATUS_DEV) != CYAPA_DEV_NORMAL ||
	    (data.finger_btn & OP_DATA_VALID) != OP_DATA_VALID) {
		dev_err(dev, "invalid device state bytes: %02x %02x\n",
			data.device_status, data.finger_btn);
		return -EINVAL;
	}

	return cyapa_gen3_event_process(cyapa, &data);
}