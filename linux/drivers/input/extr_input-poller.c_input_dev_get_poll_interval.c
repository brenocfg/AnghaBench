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
struct input_dev {TYPE_1__* poller; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int poll_interval; } ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct input_dev* to_input_dev (struct device*) ; 

__attribute__((used)) static ssize_t input_dev_get_poll_interval(struct device *dev,
					   struct device_attribute *attr,
					   char *buf)
{
	struct input_dev *input = to_input_dev(dev);

	return sprintf(buf, "%d\n", input->poller->poll_interval);
}