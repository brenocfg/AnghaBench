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
struct wusbhc {TYPE_1__* wuie_host_info; } ;
struct wusb_ckhdid {int /*<<< orphan*/  data; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {struct wusb_ckhdid CHID; } ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ) ; 
 struct wusbhc* usbhc_dev_to_wusbhc (struct device*) ; 
 struct wusb_ckhdid wusb_ckhdid_zero ; 

__attribute__((used)) static ssize_t wusb_chid_show(struct device *dev,
			      struct device_attribute *attr, char *buf)
{
	struct wusbhc *wusbhc = usbhc_dev_to_wusbhc(dev);
	const struct wusb_ckhdid *chid;

	if (wusbhc->wuie_host_info != NULL)
		chid = &wusbhc->wuie_host_info->CHID;
	else
		chid = &wusb_ckhdid_zero;

	return sprintf(buf, "%16ph\n", chid->data);
}