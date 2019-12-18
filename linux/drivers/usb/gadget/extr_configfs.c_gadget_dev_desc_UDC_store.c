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
struct TYPE_4__ {char* udc_name; } ;
struct TYPE_3__ {TYPE_2__ gadget_driver; } ;
struct gadget_info {int /*<<< orphan*/  lock; TYPE_1__ composite; } ;
struct config_item {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int EBUSY ; 
 size_t ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kstrdup (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 struct gadget_info* to_gadget_info (struct config_item*) ; 
 int unregister_gadget (struct gadget_info*) ; 
 int usb_gadget_probe_driver (TYPE_2__*) ; 

__attribute__((used)) static ssize_t gadget_dev_desc_UDC_store(struct config_item *item,
		const char *page, size_t len)
{
	struct gadget_info *gi = to_gadget_info(item);
	char *name;
	int ret;

	name = kstrdup(page, GFP_KERNEL);
	if (!name)
		return -ENOMEM;
	if (name[len - 1] == '\n')
		name[len - 1] = '\0';

	mutex_lock(&gi->lock);

	if (!strlen(name)) {
		ret = unregister_gadget(gi);
		if (ret)
			goto err;
		kfree(name);
	} else {
		if (gi->composite.gadget_driver.udc_name) {
			ret = -EBUSY;
			goto err;
		}
		gi->composite.gadget_driver.udc_name = name;
		ret = usb_gadget_probe_driver(&gi->composite.gadget_driver);
		if (ret) {
			gi->composite.gadget_driver.udc_name = NULL;
			goto err;
		}
	}
	mutex_unlock(&gi->lock);
	return len;
err:
	kfree(name);
	mutex_unlock(&gi->lock);
	return ret;
}