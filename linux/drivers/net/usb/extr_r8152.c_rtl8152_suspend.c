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
struct r8152 {int /*<<< orphan*/  control; } ;
typedef  int /*<<< orphan*/  pm_message_t ;

/* Variables and functions */
 scalar_t__ PMSG_IS_AUTO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int rtl8152_runtime_suspend (struct r8152*) ; 
 int rtl8152_system_suspend (struct r8152*) ; 
 struct r8152* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static int rtl8152_suspend(struct usb_interface *intf, pm_message_t message)
{
	struct r8152 *tp = usb_get_intfdata(intf);
	int ret;

	mutex_lock(&tp->control);

	if (PMSG_IS_AUTO(message))
		ret = rtl8152_runtime_suspend(tp);
	else
		ret = rtl8152_system_suspend(tp);

	mutex_unlock(&tp->control);

	return ret;
}