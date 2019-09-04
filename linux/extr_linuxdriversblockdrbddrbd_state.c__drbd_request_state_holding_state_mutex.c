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
typedef  union drbd_state {int dummy; } drbd_state ;
struct drbd_device {int /*<<< orphan*/  state_mutex; int /*<<< orphan*/  state_wait; } ;
typedef  enum drbd_state_rv { ____Placeholder_drbd_state_rv } drbd_state_rv ;
typedef  enum chg_state_flags { ____Placeholder_chg_state_flags } chg_state_flags ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int CS_SERIALIZE ; 
 int SS_IN_TRANSIENT_STATE ; 
 int drbd_req_state (struct drbd_device*,union drbd_state,union drbd_state,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event_cmd (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

enum drbd_state_rv
_drbd_request_state_holding_state_mutex(struct drbd_device *device, union drbd_state mask,
		    union drbd_state val, enum chg_state_flags f)
{
	enum drbd_state_rv rv;

	BUG_ON(f & CS_SERIALIZE);

	wait_event_cmd(device->state_wait,
		       (rv = drbd_req_state(device, mask, val, f)) != SS_IN_TRANSIENT_STATE,
		       mutex_unlock(device->state_mutex),
		       mutex_lock(device->state_mutex));

	return rv;
}