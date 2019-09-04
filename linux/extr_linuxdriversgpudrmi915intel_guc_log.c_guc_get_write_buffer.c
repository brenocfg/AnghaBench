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
struct TYPE_2__ {int /*<<< orphan*/  channel; } ;
struct intel_guc_log {TYPE_1__ relay; } ;

/* Variables and functions */
 void* relay_reserve (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *guc_get_write_buffer(struct intel_guc_log *log)
{
	/*
	 * Just get the base address of a new sub buffer and copy data into it
	 * ourselves. NULL will be returned in no-overwrite mode, if all sub
	 * buffers are full. Could have used the relay_write() to indirectly
	 * copy the data, but that would have been bit convoluted, as we need to
	 * write to only certain locations inside a sub buffer which cannot be
	 * done without using relay_reserve() along with relay_write(). So its
	 * better to use relay_reserve() alone.
	 */
	return relay_reserve(log->relay.channel, 0);
}