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
struct wusbhc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wusbhc_attr_group ; 
 int /*<<< orphan*/  wusbhc_kobj (struct wusbhc*) ; 
 int /*<<< orphan*/  wusbhc_pal_unregister (struct wusbhc*) ; 

void wusbhc_b_destroy(struct wusbhc *wusbhc)
{
	wusbhc_pal_unregister(wusbhc);
	sysfs_remove_group(wusbhc_kobj(wusbhc), &wusbhc_attr_group);
}