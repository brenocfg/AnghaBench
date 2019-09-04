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
struct TYPE_2__ {int flags; } ;
struct wiimote_data {TYPE_1__ state; } ;
typedef  int __u8 ;

/* Variables and functions */
 int WIIPROTO_FLAG_ACCEL ; 
 int /*<<< orphan*/  WIIPROTO_REQ_NULL ; 
 int /*<<< orphan*/  wiiproto_req_drm (struct wiimote_data*,int /*<<< orphan*/ ) ; 

void wiiproto_req_accel(struct wiimote_data *wdata, __u8 accel)
{
	accel = !!accel;
	if (accel == !!(wdata->state.flags & WIIPROTO_FLAG_ACCEL))
		return;

	if (accel)
		wdata->state.flags |= WIIPROTO_FLAG_ACCEL;
	else
		wdata->state.flags &= ~WIIPROTO_FLAG_ACCEL;

	wiiproto_req_drm(wdata, WIIPROTO_REQ_NULL);
}