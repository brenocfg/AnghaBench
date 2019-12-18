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
typedef  scalar_t__ u16 ;
struct ast_vhub_dev {int wakeup_en; } ;

/* Variables and functions */
 int /*<<< orphan*/  DDBG (struct ast_vhub_dev*,char*,char*,scalar_t__) ; 
 scalar_t__ USB_DEVICE_REMOTE_WAKEUP ; 
 int std_req_complete ; 
 int std_req_driver ; 

__attribute__((used)) static int ast_vhub_dev_feature(struct ast_vhub_dev *d,
				u16 wIndex, u16 wValue,
				bool is_set)
{
	DDBG(d, "%s_FEATURE(dev val=%02x)\n",
	     is_set ? "SET" : "CLEAR", wValue);

	if (wValue != USB_DEVICE_REMOTE_WAKEUP)
		return std_req_driver;

	d->wakeup_en = is_set;

	return std_req_complete;
}