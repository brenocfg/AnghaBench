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
struct TYPE_2__ {int /*<<< orphan*/  sem; } ;

/* Variables and functions */
 int RDMA_NL_NUM_CLIENTS ; 
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 
 TYPE_1__* rdma_nl_types ; 

void rdma_nl_init(void)
{
	int idx;

	for (idx = 0; idx < RDMA_NL_NUM_CLIENTS; idx++)
		init_rwsem(&rdma_nl_types[idx].sem);
}