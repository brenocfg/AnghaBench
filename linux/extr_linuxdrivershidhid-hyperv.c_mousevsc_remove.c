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
struct mousevsc_dev {int /*<<< orphan*/  hid_device; } ;
struct hv_device {int /*<<< orphan*/  channel; int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_init_wakeup (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hid_destroy_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hid_hw_stop (int /*<<< orphan*/ ) ; 
 struct mousevsc_dev* hv_get_drvdata (struct hv_device*) ; 
 int /*<<< orphan*/  mousevsc_free_device (struct mousevsc_dev*) ; 
 int /*<<< orphan*/  vmbus_close (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mousevsc_remove(struct hv_device *dev)
{
	struct mousevsc_dev *input_dev = hv_get_drvdata(dev);

	device_init_wakeup(&dev->device, false);
	vmbus_close(dev->channel);
	hid_hw_stop(input_dev->hid_device);
	hid_destroy_device(input_dev->hid_device);
	mousevsc_free_device(input_dev);

	return 0;
}