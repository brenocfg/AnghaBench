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
struct TYPE_2__ {struct device* parent; } ;
struct rtc_device {int id; TYPE_1__ dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct rtc_device* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_set_name (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  devm_rtc_release_device ; 
 int /*<<< orphan*/  devres_add (struct device*,struct rtc_device**) ; 
 struct rtc_device** devres_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_free (struct rtc_device**) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int) ; 
 struct rtc_device* rtc_allocate_device () ; 
 int rtc_device_get_id (struct device*) ; 
 int /*<<< orphan*/  rtc_ida ; 

struct rtc_device *devm_rtc_allocate_device(struct device *dev)
{
	struct rtc_device **ptr, *rtc;
	int id, err;

	id = rtc_device_get_id(dev);
	if (id < 0)
		return ERR_PTR(id);

	ptr = devres_alloc(devm_rtc_release_device, sizeof(*ptr), GFP_KERNEL);
	if (!ptr) {
		err = -ENOMEM;
		goto exit_ida;
	}

	rtc = rtc_allocate_device();
	if (!rtc) {
		err = -ENOMEM;
		goto exit_devres;
	}

	*ptr = rtc;
	devres_add(dev, ptr);

	rtc->id = id;
	rtc->dev.parent = dev;
	dev_set_name(&rtc->dev, "rtc%d", id);

	return rtc;

exit_devres:
	devres_free(ptr);
exit_ida:
	ida_simple_remove(&rtc_ida, id);
	return ERR_PTR(err);
}