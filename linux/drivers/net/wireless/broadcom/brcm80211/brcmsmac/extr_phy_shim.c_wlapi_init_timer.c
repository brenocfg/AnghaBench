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
struct wlapi_timer {int dummy; } ;
struct phy_shim_info {int /*<<< orphan*/  wl; } ;

/* Variables and functions */
 scalar_t__ brcms_init_timer (int /*<<< orphan*/ ,void (*) (void*),void*,char const*) ; 

struct wlapi_timer *wlapi_init_timer(struct phy_shim_info *physhim,
				     void (*fn)(struct brcms_phy *pi),
				     void *arg, const char *name)
{
	return (struct wlapi_timer *)
			brcms_init_timer(physhim->wl, (void (*)(void *))fn,
					 arg, name);
}