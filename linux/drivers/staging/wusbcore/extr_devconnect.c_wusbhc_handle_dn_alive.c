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
typedef  int /*<<< orphan*/  u8 ;
struct wusbhc {int /*<<< orphan*/  mutex; int /*<<< orphan*/  dev; } ;
struct wusb_dev {int /*<<< orphan*/  entry_ts; } ;

/* Variables and functions */
 int /*<<< orphan*/  __wusbhc_keep_alive (struct wusbhc*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct wusb_dev* wusbhc_find_dev_by_addr (struct wusbhc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wusbhc_handle_dn_alive(struct wusbhc *wusbhc, u8 srcaddr)
{
	struct wusb_dev *wusb_dev;

	mutex_lock(&wusbhc->mutex);
	wusb_dev = wusbhc_find_dev_by_addr(wusbhc, srcaddr);
	if (wusb_dev == NULL) {
		dev_dbg(wusbhc->dev, "ignoring DN_Alive from unconnected device %02x\n",
			srcaddr);
	} else {
		wusb_dev->entry_ts = jiffies;
		__wusbhc_keep_alive(wusbhc);
	}
	mutex_unlock(&wusbhc->mutex);
}