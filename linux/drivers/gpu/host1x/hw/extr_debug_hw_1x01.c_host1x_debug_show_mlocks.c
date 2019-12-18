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
typedef  int /*<<< orphan*/  u32 ;
struct output {int dummy; } ;
struct host1x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HOST1X_SYNC_MLOCK_OWNER (unsigned int) ; 
 int /*<<< orphan*/  HOST1X_SYNC_MLOCK_OWNER_CHID_V (int /*<<< orphan*/ ) ; 
 scalar_t__ HOST1X_SYNC_MLOCK_OWNER_CH_OWNS_V (int /*<<< orphan*/ ) ; 
 scalar_t__ HOST1X_SYNC_MLOCK_OWNER_CPU_OWNS_V (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  host1x_debug_output (struct output*,char*,...) ; 
 int /*<<< orphan*/  host1x_sync_readl (struct host1x*,int /*<<< orphan*/ ) ; 
 unsigned int host1x_syncpt_nb_mlocks (struct host1x*) ; 

__attribute__((used)) static void host1x_debug_show_mlocks(struct host1x *host, struct output *o)
{
	unsigned int i;

	host1x_debug_output(o, "---- mlocks ----\n");

	for (i = 0; i < host1x_syncpt_nb_mlocks(host); i++) {
		u32 owner =
			host1x_sync_readl(host, HOST1X_SYNC_MLOCK_OWNER(i));
		if (HOST1X_SYNC_MLOCK_OWNER_CH_OWNS_V(owner))
			host1x_debug_output(o, "%u: locked by channel %u\n",
				i, HOST1X_SYNC_MLOCK_OWNER_CHID_V(owner));
		else if (HOST1X_SYNC_MLOCK_OWNER_CPU_OWNS_V(owner))
			host1x_debug_output(o, "%u: locked by cpu\n", i);
		else
			host1x_debug_output(o, "%u: unlocked\n", i);
	}

	host1x_debug_output(o, "\n");
}