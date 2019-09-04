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
struct hid_device {TYPE_1__* ll_driver; } ;
typedef  int /*<<< orphan*/  __u8 ;
struct TYPE_2__ {int /*<<< orphan*/  output_report; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int hid_hw_output_report (struct hid_device*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmemdup (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wiimote_hid_send(struct hid_device *hdev, __u8 *buffer,
			    size_t count)
{
	__u8 *buf;
	int ret;

	if (!hdev->ll_driver->output_report)
		return -ENODEV;

	buf = kmemdup(buffer, count, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	ret = hid_hw_output_report(hdev, buf, count);

	kfree(buf);
	return ret;
}