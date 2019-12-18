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
struct vmbus_channel {int /*<<< orphan*/  sc_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  invoke_sc_cb (struct vmbus_channel*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

bool vmbus_are_subchannels_present(struct vmbus_channel *primary)
{
	bool ret;

	ret = !list_empty(&primary->sc_list);

	if (ret) {
		/*
		 * Invoke the callback on sub-channel creation.
		 * This will present a uniform interface to the
		 * clients.
		 */
		invoke_sc_cb(primary);
	}

	return ret;
}