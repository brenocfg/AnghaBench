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
struct TYPE_3__ {int /*<<< orphan*/  count; int /*<<< orphan*/  buffer; int /*<<< orphan*/  slave_adr; } ;
struct nmk_i2c_dev {int stop; TYPE_2__* adev; scalar_t__ result; TYPE_1__ cli; } ;
struct i2c_msg {int /*<<< orphan*/  flags; int /*<<< orphan*/  len; int /*<<< orphan*/  buf; int /*<<< orphan*/  addr; } ;
struct i2c_adapter {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct nmk_i2c_dev* i2c_get_adapdata (struct i2c_adapter*) ; 
 int nmk_i2c_xfer_one (struct nmk_i2c_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setup_i2c_controller (struct nmk_i2c_dev*) ; 

__attribute__((used)) static int nmk_i2c_xfer(struct i2c_adapter *i2c_adap,
		struct i2c_msg msgs[], int num_msgs)
{
	int status = 0;
	int i;
	struct nmk_i2c_dev *dev = i2c_get_adapdata(i2c_adap);
	int j;

	pm_runtime_get_sync(&dev->adev->dev);

	/* Attempt three times to send the message queue */
	for (j = 0; j < 3; j++) {
		/* setup the i2c controller */
		setup_i2c_controller(dev);

		for (i = 0; i < num_msgs; i++) {
			dev->cli.slave_adr	= msgs[i].addr;
			dev->cli.buffer		= msgs[i].buf;
			dev->cli.count		= msgs[i].len;
			dev->stop = (i < (num_msgs - 1)) ? 0 : 1;
			dev->result = 0;

			status = nmk_i2c_xfer_one(dev, msgs[i].flags);
			if (status != 0)
				break;
		}
		if (status == 0)
			break;
	}

	pm_runtime_put_sync(&dev->adev->dev);

	/* return the no. messages processed */
	if (status)
		return status;
	else
		return num_msgs;
}