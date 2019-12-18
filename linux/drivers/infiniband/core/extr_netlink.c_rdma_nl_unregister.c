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
struct TYPE_2__ {int /*<<< orphan*/  sem; int /*<<< orphan*/ * cb_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 TYPE_1__* rdma_nl_types ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void rdma_nl_unregister(unsigned int index)
{
	down_write(&rdma_nl_types[index].sem);
	rdma_nl_types[index].cb_table = NULL;
	up_write(&rdma_nl_types[index].sem);
}