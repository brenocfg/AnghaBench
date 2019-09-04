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
struct drbd_state_change {unsigned int n_connections; unsigned int n_devices; struct drbd_peer_device_state_change* peer_devices; struct drbd_device_state_change* devices; struct drbd_connection_state_change* connections; struct drbd_resource_state_change* resource; } ;
struct drbd_resource_state_change {int /*<<< orphan*/ * susp_fen; int /*<<< orphan*/ * susp_nod; int /*<<< orphan*/ * susp; int /*<<< orphan*/ * role; } ;
struct drbd_peer_device_state_change {int /*<<< orphan*/ * resync_susp_dependency; int /*<<< orphan*/ * resync_susp_peer; int /*<<< orphan*/ * resync_susp_user; int /*<<< orphan*/ * repl_state; int /*<<< orphan*/ * disk_state; } ;
struct drbd_device_state_change {int /*<<< orphan*/ * disk_state; } ;
struct drbd_connection_state_change {int /*<<< orphan*/ * cstate; int /*<<< orphan*/ * peer_role; } ;

/* Variables and functions */
 size_t NEW ; 
 size_t OLD ; 

void copy_old_to_new_state_change(struct drbd_state_change *state_change)
{
	struct drbd_resource_state_change *resource_state_change = &state_change->resource[0];
	unsigned int n_device, n_connection, n_peer_device, n_peer_devices;

#define OLD_TO_NEW(x) \
	(x[NEW] = x[OLD])

	OLD_TO_NEW(resource_state_change->role);
	OLD_TO_NEW(resource_state_change->susp);
	OLD_TO_NEW(resource_state_change->susp_nod);
	OLD_TO_NEW(resource_state_change->susp_fen);

	for (n_connection = 0; n_connection < state_change->n_connections; n_connection++) {
		struct drbd_connection_state_change *connection_state_change =
				&state_change->connections[n_connection];

		OLD_TO_NEW(connection_state_change->peer_role);
		OLD_TO_NEW(connection_state_change->cstate);
	}

	for (n_device = 0; n_device < state_change->n_devices; n_device++) {
		struct drbd_device_state_change *device_state_change =
			&state_change->devices[n_device];

		OLD_TO_NEW(device_state_change->disk_state);
	}

	n_peer_devices = state_change->n_devices * state_change->n_connections;
	for (n_peer_device = 0; n_peer_device < n_peer_devices; n_peer_device++) {
		struct drbd_peer_device_state_change *p =
			&state_change->peer_devices[n_peer_device];

		OLD_TO_NEW(p->disk_state);
		OLD_TO_NEW(p->repl_state);
		OLD_TO_NEW(p->resync_susp_user);
		OLD_TO_NEW(p->resync_susp_peer);
		OLD_TO_NEW(p->resync_susp_dependency);
	}

#undef OLD_TO_NEW
}