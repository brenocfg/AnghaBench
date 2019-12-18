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
struct wusbhc {scalar_t__ uwb_rc; } ;

/* Variables and functions */
 int /*<<< orphan*/  uwb_rc_reset_all (scalar_t__) ; 

void wusbhc_reset_all(struct wusbhc *wusbhc)
{
	if (wusbhc->uwb_rc)
		uwb_rc_reset_all(wusbhc->uwb_rc);
}