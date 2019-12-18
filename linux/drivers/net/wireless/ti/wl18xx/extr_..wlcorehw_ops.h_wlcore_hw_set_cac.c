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
struct wl12xx_vif {int dummy; } ;
struct wl1271 {TYPE_1__* ops; } ;
struct TYPE_2__ {int (* set_cac ) (struct wl1271*,struct wl12xx_vif*,int) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int stub1 (struct wl1271*,struct wl12xx_vif*,int) ; 

__attribute__((used)) static inline int
wlcore_hw_set_cac(struct wl1271 *wl, struct wl12xx_vif *wlvif, bool start)
{
	if (!wl->ops->set_cac)
		return -EINVAL;

	return wl->ops->set_cac(wl, wlvif, start);
}