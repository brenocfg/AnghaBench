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
struct usb_interface {int dummy; } ;
struct rtsx_ucr {int /*<<< orphan*/  dev_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static int rtsx_usb_pre_reset(struct usb_interface *intf)
{
	struct rtsx_ucr *ucr = (struct rtsx_ucr *)usb_get_intfdata(intf);

	mutex_lock(&ucr->dev_mutex);
	return 0;
}