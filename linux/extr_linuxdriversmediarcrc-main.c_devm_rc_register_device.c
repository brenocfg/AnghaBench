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
struct rc_dev {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  devm_rc_release ; 
 int /*<<< orphan*/  devres_add (struct device*,struct rc_dev**) ; 
 struct rc_dev** devres_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_free (struct rc_dev**) ; 
 int rc_register_device (struct rc_dev*) ; 

int devm_rc_register_device(struct device *parent, struct rc_dev *dev)
{
	struct rc_dev **dr;
	int ret;

	dr = devres_alloc(devm_rc_release, sizeof(*dr), GFP_KERNEL);
	if (!dr)
		return -ENOMEM;

	ret = rc_register_device(dev);
	if (ret) {
		devres_free(dr);
		return ret;
	}

	*dr = dev;
	devres_add(parent, dr);

	return 0;
}