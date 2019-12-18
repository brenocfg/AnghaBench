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
struct device {int dummy; } ;
struct abx500_ops {int dummy; } ;
struct abx500_device_entry {int /*<<< orphan*/  list; int /*<<< orphan*/  ops; struct device* dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  abx500_list ; 
 struct abx500_device_entry* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct abx500_ops*,int) ; 

int abx500_register_ops(struct device *dev, struct abx500_ops *ops)
{
	struct abx500_device_entry *dev_entry;

	dev_entry = devm_kzalloc(dev, sizeof(*dev_entry), GFP_KERNEL);
	if (!dev_entry)
		return -ENOMEM;

	dev_entry->dev = dev;
	memcpy(&dev_entry->ops, ops, sizeof(*ops));

	list_add_tail(&dev_entry->list, &abx500_list);
	return 0;
}