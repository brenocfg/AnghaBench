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
struct input_dev {int dummy; } ;
struct atkbd {unsigned int softraw; struct input_dev* dev; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  atkbd_set_device_attrs (struct atkbd*) ; 
 struct input_dev* input_allocate_device () ; 
 int /*<<< orphan*/  input_free_device (struct input_dev*) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_unregister_device (struct input_dev*) ; 
 int kstrtouint (char const*,int,unsigned int*) ; 

__attribute__((used)) static ssize_t atkbd_set_softraw(struct atkbd *atkbd, const char *buf, size_t count)
{
	struct input_dev *old_dev, *new_dev;
	unsigned int value;
	int err;
	bool old_softraw;

	err = kstrtouint(buf, 10, &value);
	if (err)
		return err;

	if (value > 1)
		return -EINVAL;

	if (atkbd->softraw != value) {
		old_dev = atkbd->dev;
		old_softraw = atkbd->softraw;

		new_dev = input_allocate_device();
		if (!new_dev)
			return -ENOMEM;

		atkbd->dev = new_dev;
		atkbd->softraw = value;
		atkbd_set_device_attrs(atkbd);

		err = input_register_device(atkbd->dev);
		if (err) {
			input_free_device(new_dev);

			atkbd->dev = old_dev;
			atkbd->softraw = old_softraw;
			atkbd_set_device_attrs(atkbd);

			return err;
		}
		input_unregister_device(old_dev);
	}
	return count;
}