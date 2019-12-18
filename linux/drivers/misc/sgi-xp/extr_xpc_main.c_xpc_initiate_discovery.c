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

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xpc_discovery () ; 
 int /*<<< orphan*/  xpc_discovery_exited ; 
 int /*<<< orphan*/  xpc_part ; 

__attribute__((used)) static int
xpc_initiate_discovery(void *ignore)
{
	xpc_discovery();

	dev_dbg(xpc_part, "discovery thread is exiting\n");

	/* mark this thread as having exited */
	complete(&xpc_discovery_exited);
	return 0;
}