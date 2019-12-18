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
struct wacom {scalar_t__ hdev; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hid_hw_close (scalar_t__) ; 
 struct wacom* input_get_drvdata (struct input_dev*) ; 

__attribute__((used)) static void wacom_close(struct input_dev *dev)
{
	struct wacom *wacom = input_get_drvdata(dev);

	/*
	 * wacom->hdev should never be null, but surprisingly, I had the case
	 * once while unplugging the Wacom Wireless Receiver.
	 */
	if (wacom->hdev)
		hid_hw_close(wacom->hdev);
}