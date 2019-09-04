#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct input_polled_dev {int /*<<< orphan*/  input; int /*<<< orphan*/  poll_interval_max; int /*<<< orphan*/  poll_interval_min; int /*<<< orphan*/  poll_interval; int /*<<< orphan*/  poll; int /*<<< orphan*/  close; int /*<<< orphan*/  open; struct bma150_data* private; } ;
struct bma150_data {int /*<<< orphan*/  input; struct input_polled_dev* input_polled; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMA150_POLL_INTERVAL ; 
 int /*<<< orphan*/  BMA150_POLL_MAX ; 
 int /*<<< orphan*/  BMA150_POLL_MIN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  bma150_init_input_device (struct bma150_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bma150_poll ; 
 int /*<<< orphan*/  bma150_poll_close ; 
 int /*<<< orphan*/  bma150_poll_open ; 
 struct input_polled_dev* input_allocate_polled_device () ; 
 int /*<<< orphan*/  input_free_polled_device (struct input_polled_dev*) ; 
 int input_register_polled_device (struct input_polled_dev*) ; 

__attribute__((used)) static int bma150_register_polled_device(struct bma150_data *bma150)
{
	struct input_polled_dev *ipoll_dev;
	int error;

	ipoll_dev = input_allocate_polled_device();
	if (!ipoll_dev)
		return -ENOMEM;

	ipoll_dev->private = bma150;
	ipoll_dev->open = bma150_poll_open;
	ipoll_dev->close = bma150_poll_close;
	ipoll_dev->poll = bma150_poll;
	ipoll_dev->poll_interval = BMA150_POLL_INTERVAL;
	ipoll_dev->poll_interval_min = BMA150_POLL_MIN;
	ipoll_dev->poll_interval_max = BMA150_POLL_MAX;

	bma150_init_input_device(bma150, ipoll_dev->input);

	bma150->input_polled = ipoll_dev;
	bma150->input = ipoll_dev->input;

	error = input_register_polled_device(ipoll_dev);
	if (error) {
		input_free_polled_device(ipoll_dev);
		return error;
	}

	return 0;
}