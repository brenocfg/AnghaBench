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
struct hid_device {struct hid_device* dev_rdesc; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hid_close_report (struct hid_device*) ; 
 int /*<<< orphan*/  kfree (struct hid_device*) ; 
 struct hid_device* to_hid_device (struct device*) ; 

__attribute__((used)) static void hid_device_release(struct device *dev)
{
	struct hid_device *hid = to_hid_device(dev);

	hid_close_report(hid);
	kfree(hid->dev_rdesc);
	kfree(hid);
}