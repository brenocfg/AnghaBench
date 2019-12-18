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
struct vchiq_state {TYPE_1__* remote; } ;
struct vchiq_header {int /*<<< orphan*/  msgid; } ;
struct TYPE_2__ {int /*<<< orphan*/  sync_release; } ;

/* Variables and functions */
 int /*<<< orphan*/  VCHIQ_MSGID_PADDING ; 
 int /*<<< orphan*/  remote_event_signal (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
release_message_sync(struct vchiq_state *state, struct vchiq_header *header)
{
	header->msgid = VCHIQ_MSGID_PADDING;
	remote_event_signal(&state->remote->sync_release);
}