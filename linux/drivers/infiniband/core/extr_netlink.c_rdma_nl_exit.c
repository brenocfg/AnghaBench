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
struct TYPE_2__ {int /*<<< orphan*/  cb_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 int RDMA_NL_NUM_CLIENTS ; 
 int /*<<< orphan*/  WARN (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* rdma_nl_types ; 

void rdma_nl_exit(void)
{
	int idx;

	for (idx = 0; idx < RDMA_NL_NUM_CLIENTS; idx++)
		WARN(rdma_nl_types[idx].cb_table,
		     "Netlink client %d wasn't released prior to unloading %s\n",
		     idx, KBUILD_MODNAME);
}