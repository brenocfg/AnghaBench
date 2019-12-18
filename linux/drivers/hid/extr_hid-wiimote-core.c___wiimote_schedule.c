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
struct wiimote_data {int /*<<< orphan*/  init_worker; TYPE_1__ state; } ;

/* Variables and functions */
 int WIIPROTO_FLAG_EXITING ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

void __wiimote_schedule(struct wiimote_data *wdata)
{
	if (!(wdata->state.flags & WIIPROTO_FLAG_EXITING))
		schedule_work(&wdata->init_worker);
}