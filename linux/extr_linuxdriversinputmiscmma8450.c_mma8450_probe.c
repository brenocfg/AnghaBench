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
struct mma8450 {struct input_polled_dev* idev; struct i2c_client* client; } ;
struct input_polled_dev {TYPE_2__* input; int /*<<< orphan*/  close; int /*<<< orphan*/  open; int /*<<< orphan*/  poll_interval_max; int /*<<< orphan*/  poll_interval; int /*<<< orphan*/  poll; struct mma8450* private; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  bustype; } ;
struct TYPE_4__ {int /*<<< orphan*/  evbit; TYPE_1__ id; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  ABS_Z ; 
 int /*<<< orphan*/  BUS_I2C ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_ABS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MMA8450_DRV_NAME ; 
 int /*<<< orphan*/  POLL_INTERVAL ; 
 int /*<<< orphan*/  POLL_INTERVAL_MAX ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct input_polled_dev* devm_input_allocate_polled_device (int /*<<< orphan*/ *) ; 
 struct mma8450* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int input_register_polled_device (struct input_polled_dev*) ; 
 int /*<<< orphan*/  input_set_abs_params (TYPE_2__*,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  mma8450_close ; 
 int /*<<< orphan*/  mma8450_open ; 
 int /*<<< orphan*/  mma8450_poll ; 

__attribute__((used)) static int mma8450_probe(struct i2c_client *c,
			 const struct i2c_device_id *id)
{
	struct input_polled_dev *idev;
	struct mma8450 *m;
	int err;

	m = devm_kzalloc(&c->dev, sizeof(*m), GFP_KERNEL);
	if (!m)
		return -ENOMEM;

	idev = devm_input_allocate_polled_device(&c->dev);
	if (!idev)
		return -ENOMEM;

	m->client = c;
	m->idev = idev;

	idev->private		= m;
	idev->input->name	= MMA8450_DRV_NAME;
	idev->input->id.bustype	= BUS_I2C;
	idev->poll		= mma8450_poll;
	idev->poll_interval	= POLL_INTERVAL;
	idev->poll_interval_max	= POLL_INTERVAL_MAX;
	idev->open		= mma8450_open;
	idev->close		= mma8450_close;

	__set_bit(EV_ABS, idev->input->evbit);
	input_set_abs_params(idev->input, ABS_X, -2048, 2047, 32, 32);
	input_set_abs_params(idev->input, ABS_Y, -2048, 2047, 32, 32);
	input_set_abs_params(idev->input, ABS_Z, -2048, 2047, 32, 32);

	err = input_register_polled_device(idev);
	if (err) {
		dev_err(&c->dev, "failed to register polled input device\n");
		return err;
	}

	return 0;
}