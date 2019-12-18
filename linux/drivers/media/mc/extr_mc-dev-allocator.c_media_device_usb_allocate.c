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
struct usb_device {int /*<<< orphan*/  product; int /*<<< orphan*/  dev; } ;
struct module {int dummy; } ;
struct media_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct media_device* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct media_device* __media_device_get (int /*<<< orphan*/ *,char const*,struct module*) ; 
 int /*<<< orphan*/  __media_device_usb_init (struct media_device*,struct usb_device*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  media_device_lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

struct media_device *media_device_usb_allocate(struct usb_device *udev,
					       const char *module_name,
					       struct module *owner)
{
	struct media_device *mdev;

	mutex_lock(&media_device_lock);
	mdev = __media_device_get(&udev->dev, module_name, owner);
	if (!mdev) {
		mutex_unlock(&media_device_lock);
		return ERR_PTR(-ENOMEM);
	}

	/* check if media device is already initialized */
	if (!mdev->dev)
		__media_device_usb_init(mdev, udev, udev->product,
					module_name);
	mutex_unlock(&media_device_lock);
	return mdev;
}