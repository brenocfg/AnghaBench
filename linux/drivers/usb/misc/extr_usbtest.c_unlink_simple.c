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
struct usbtest_dev {int dummy; } ;

/* Variables and functions */
 int unlink1 (struct usbtest_dev*,int,int,int) ; 

__attribute__((used)) static int unlink_simple(struct usbtest_dev *dev, int pipe, int len)
{
	int			retval = 0;

	/* test sync and async paths */
	retval = unlink1(dev, pipe, len, 1);
	if (!retval)
		retval = unlink1(dev, pipe, len, 0);
	return retval;
}