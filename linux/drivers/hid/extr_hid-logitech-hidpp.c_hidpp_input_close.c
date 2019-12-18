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
struct input_dev {int dummy; } ;
struct hid_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hid_hw_close (struct hid_device*) ; 
 struct hid_device* input_get_drvdata (struct input_dev*) ; 

__attribute__((used)) static void hidpp_input_close(struct input_dev *dev)
{
	struct hid_device *hid = input_get_drvdata(dev);

	hid_hw_close(hid);
}