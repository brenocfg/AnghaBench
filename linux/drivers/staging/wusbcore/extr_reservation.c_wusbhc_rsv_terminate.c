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
struct wusbhc {int /*<<< orphan*/ * rsv; } ;

/* Variables and functions */
 int /*<<< orphan*/  uwb_rsv_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uwb_rsv_terminate (int /*<<< orphan*/ *) ; 

void wusbhc_rsv_terminate(struct wusbhc *wusbhc)
{
	if (wusbhc->rsv) {
		uwb_rsv_terminate(wusbhc->rsv);
		uwb_rsv_destroy(wusbhc->rsv);
		wusbhc->rsv = NULL;
	}
}