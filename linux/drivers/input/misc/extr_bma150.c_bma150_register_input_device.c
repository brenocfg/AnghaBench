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
struct input_dev {int /*<<< orphan*/  close; int /*<<< orphan*/  open; } ;
struct bma150_data {struct input_dev* input; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  bma150_init_input_device (struct bma150_data*,struct input_dev*) ; 
 int /*<<< orphan*/  bma150_irq_close ; 
 int /*<<< orphan*/  bma150_irq_open ; 
 struct input_dev* input_allocate_device () ; 
 int /*<<< orphan*/  input_free_device (struct input_dev*) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_drvdata (struct input_dev*,struct bma150_data*) ; 

__attribute__((used)) static int bma150_register_input_device(struct bma150_data *bma150)
{
	struct input_dev *idev;
	int error;

	idev = input_allocate_device();
	if (!idev)
		return -ENOMEM;

	bma150_init_input_device(bma150, idev);

	idev->open = bma150_irq_open;
	idev->close = bma150_irq_close;
	input_set_drvdata(idev, bma150);

	bma150->input = idev;

	error = input_register_device(idev);
	if (error) {
		input_free_device(idev);
		return error;
	}

	return 0;
}