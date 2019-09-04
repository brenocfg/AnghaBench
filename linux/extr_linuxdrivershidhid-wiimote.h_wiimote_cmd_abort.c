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
struct TYPE_2__ {int /*<<< orphan*/  ready; int /*<<< orphan*/  cmd; } ;
struct wiimote_data {TYPE_1__ state; } ;

/* Variables and functions */
 int /*<<< orphan*/  WIIPROTO_REQ_MAX ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void wiimote_cmd_abort(struct wiimote_data *wdata)
{
	/* Abort synchronous request by waking up the sleeping caller. But
	 * reset the state.cmd field to an invalid value so no further event
	 * handlers will work with it. */
	wdata->state.cmd = WIIPROTO_REQ_MAX;
	complete(&wdata->state.ready);
}