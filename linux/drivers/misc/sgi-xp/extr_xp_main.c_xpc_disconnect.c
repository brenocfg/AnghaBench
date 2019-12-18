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
struct xpc_registration {int /*<<< orphan*/  mutex; scalar_t__ idle_limit; scalar_t__ assigned_limit; scalar_t__ entry_size; scalar_t__ nentries; int /*<<< orphan*/ * key; int /*<<< orphan*/ * func; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* disconnect ) (int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DBUG_ON (int) ; 
 int XPC_MAX_NCHANNELS ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int) ; 
 TYPE_1__ xpc_interface ; 
 struct xpc_registration* xpc_registrations ; 

void
xpc_disconnect(int ch_number)
{
	struct xpc_registration *registration;

	DBUG_ON(ch_number < 0 || ch_number >= XPC_MAX_NCHANNELS);

	registration = &xpc_registrations[ch_number];

	/*
	 * We've decided not to make this a down_interruptible(), since we
	 * figured XPC's users will just turn around and call xpc_disconnect()
	 * again anyways, so we might as well wait, if need be.
	 */
	mutex_lock(&registration->mutex);

	/* if !XPC_CHANNEL_REGISTERED(ch_number) */
	if (registration->func == NULL) {
		mutex_unlock(&registration->mutex);
		return;
	}

	/* remove the connection registration for the specified channel */
	registration->func = NULL;
	registration->key = NULL;
	registration->nentries = 0;
	registration->entry_size = 0;
	registration->assigned_limit = 0;
	registration->idle_limit = 0;

	if (xpc_interface.disconnect)
		xpc_interface.disconnect(ch_number);

	mutex_unlock(&registration->mutex);

	return;
}