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
struct wusbhc {int /*<<< orphan*/  cack_count; } ;
struct wusb_dev {int /*<<< orphan*/  cack_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wusbhc_fill_cack_ie (struct wusbhc*) ; 

__attribute__((used)) static void wusbhc_cack_rm(struct wusbhc *wusbhc, struct wusb_dev *wusb_dev)
{
	list_del_init(&wusb_dev->cack_node);
	wusbhc->cack_count--;
	wusbhc_fill_cack_ie(wusbhc);
}