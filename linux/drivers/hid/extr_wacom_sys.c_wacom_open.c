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
struct wacom {int /*<<< orphan*/  hdev; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int hid_hw_open (int /*<<< orphan*/ ) ; 
 struct wacom* input_get_drvdata (struct input_dev*) ; 

__attribute__((used)) static int wacom_open(struct input_dev *dev)
{
	struct wacom *wacom = input_get_drvdata(dev);

	return hid_hw_open(wacom->hdev);
}