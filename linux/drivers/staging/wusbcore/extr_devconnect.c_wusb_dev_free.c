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
struct wusb_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct wusb_dev*) ; 

__attribute__((used)) static void wusb_dev_free(struct wusb_dev *wusb_dev)
{
	kfree(wusb_dev);
}