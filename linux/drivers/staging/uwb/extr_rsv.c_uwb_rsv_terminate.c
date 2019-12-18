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
struct uwb_rsv {scalar_t__ state; struct uwb_rc* rc; } ;
struct uwb_rc {int /*<<< orphan*/  rsvs_mutex; } ;

/* Variables and functions */
 scalar_t__ UWB_RSV_STATE_NONE ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uwb_rsv_set_state (struct uwb_rsv*,scalar_t__) ; 

void uwb_rsv_terminate(struct uwb_rsv *rsv)
{
	struct uwb_rc *rc = rsv->rc;

	mutex_lock(&rc->rsvs_mutex);

	if (rsv->state != UWB_RSV_STATE_NONE)
		uwb_rsv_set_state(rsv, UWB_RSV_STATE_NONE);

	mutex_unlock(&rc->rsvs_mutex);
}