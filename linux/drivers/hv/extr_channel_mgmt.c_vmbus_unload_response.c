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
struct vmbus_channel_message_header {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  unload_event; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 TYPE_1__ vmbus_connection ; 

__attribute__((used)) static void vmbus_unload_response(struct vmbus_channel_message_header *hdr)
{
	/*
	 * This is a global event; just wakeup the waiting thread.
	 * Once we successfully unload, we can cleanup the monitor state.
	 */
	complete(&vmbus_connection.unload_event);
}