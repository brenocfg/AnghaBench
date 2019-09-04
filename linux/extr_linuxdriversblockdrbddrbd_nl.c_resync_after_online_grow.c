#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ role; scalar_t__ peer; } ;
struct drbd_device {TYPE_1__ state; } ;
struct TYPE_6__ {TYPE_2__* connection; } ;
struct TYPE_5__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 scalar_t__ CS_SERIALIZE ; 
 scalar_t__ CS_VERBOSE ; 
 int /*<<< orphan*/  C_SYNC_SOURCE ; 
 int /*<<< orphan*/  C_WF_SYNC_UUID ; 
 int /*<<< orphan*/  NS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RESOLVE_CONFLICTS ; 
 scalar_t__ R_PRIMARY ; 
 int /*<<< orphan*/  _drbd_request_state (struct drbd_device*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  conn ; 
 int /*<<< orphan*/  drbd_info (struct drbd_device*,char*) ; 
 int /*<<< orphan*/  drbd_start_resync (struct drbd_device*,int /*<<< orphan*/ ) ; 
 TYPE_3__* first_peer_device (struct drbd_device*) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void resync_after_online_grow(struct drbd_device *device)
{
	int iass; /* I am sync source */

	drbd_info(device, "Resync of new storage after online grow\n");
	if (device->state.role != device->state.peer)
		iass = (device->state.role == R_PRIMARY);
	else
		iass = test_bit(RESOLVE_CONFLICTS, &first_peer_device(device)->connection->flags);

	if (iass)
		drbd_start_resync(device, C_SYNC_SOURCE);
	else
		_drbd_request_state(device, NS(conn, C_WF_SYNC_UUID), CS_VERBOSE + CS_SERIALIZE);
}