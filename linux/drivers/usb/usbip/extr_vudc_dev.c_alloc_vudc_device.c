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
struct vudc_device {int /*<<< orphan*/  pdev; int /*<<< orphan*/  dev_entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  GADGET_NAME ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct vudc_device*) ; 
 struct vudc_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_device_alloc (int /*<<< orphan*/ ,int) ; 

struct vudc_device *alloc_vudc_device(int devid)
{
	struct vudc_device *udc_dev = NULL;

	udc_dev = kzalloc(sizeof(*udc_dev), GFP_KERNEL);
	if (!udc_dev)
		goto out;

	INIT_LIST_HEAD(&udc_dev->dev_entry);

	udc_dev->pdev = platform_device_alloc(GADGET_NAME, devid);
	if (!udc_dev->pdev) {
		kfree(udc_dev);
		udc_dev = NULL;
	}

out:
	return udc_dev;
}