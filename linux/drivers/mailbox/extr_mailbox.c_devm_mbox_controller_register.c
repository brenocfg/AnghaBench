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
struct mbox_controller {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  __devm_mbox_controller_unregister ; 
 int /*<<< orphan*/  devres_add (struct device*,struct mbox_controller**) ; 
 struct mbox_controller** devres_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_free (struct mbox_controller**) ; 
 int mbox_controller_register (struct mbox_controller*) ; 

int devm_mbox_controller_register(struct device *dev,
				  struct mbox_controller *mbox)
{
	struct mbox_controller **ptr;
	int err;

	ptr = devres_alloc(__devm_mbox_controller_unregister, sizeof(*ptr),
			   GFP_KERNEL);
	if (!ptr)
		return -ENOMEM;

	err = mbox_controller_register(mbox);
	if (err < 0) {
		devres_free(ptr);
		return err;
	}

	devres_add(dev, ptr);
	*ptr = mbox;

	return 0;
}