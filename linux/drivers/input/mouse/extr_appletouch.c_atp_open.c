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
struct atp {int open; int /*<<< orphan*/  urb; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct atp* input_get_drvdata (struct input_dev*) ; 
 scalar_t__ usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int atp_open(struct input_dev *input)
{
	struct atp *dev = input_get_drvdata(input);

	if (usb_submit_urb(dev->urb, GFP_KERNEL))
		return -EIO;

	dev->open = true;
	return 0;
}