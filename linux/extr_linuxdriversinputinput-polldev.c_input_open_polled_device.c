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
struct input_polled_dev {scalar_t__ poll_interval; int /*<<< orphan*/  (* poll ) (struct input_polled_dev*) ;int /*<<< orphan*/  (* open ) (struct input_polled_dev*) ;} ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 struct input_polled_dev* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  input_polldev_queue_work (struct input_polled_dev*) ; 
 int /*<<< orphan*/  stub1 (struct input_polled_dev*) ; 
 int /*<<< orphan*/  stub2 (struct input_polled_dev*) ; 

__attribute__((used)) static int input_open_polled_device(struct input_dev *input)
{
	struct input_polled_dev *dev = input_get_drvdata(input);

	if (dev->open)
		dev->open(dev);

	/* Only start polling if polling is enabled */
	if (dev->poll_interval > 0) {
		dev->poll(dev);
		input_polldev_queue_work(dev);
	}

	return 0;
}