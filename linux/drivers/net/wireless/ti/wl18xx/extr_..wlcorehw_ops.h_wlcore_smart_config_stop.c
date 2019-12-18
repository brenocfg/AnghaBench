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
struct wl1271 {TYPE_1__* ops; } ;
struct TYPE_2__ {int (* smart_config_stop ) (struct wl1271*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int stub1 (struct wl1271*) ; 

__attribute__((used)) static inline int
wlcore_smart_config_stop(struct wl1271 *wl)
{
	if (!wl->ops->smart_config_stop)
		return -EINVAL;

	return wl->ops->smart_config_stop(wl);
}