#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct recv_comp_data {int dummy; } ;
struct netvsc_device {int recv_completion_cnt; struct netvsc_channel* chan_table; } ;
struct TYPE_3__ {scalar_t__ slots; } ;
struct netvsc_channel {TYPE_1__ mrc; TYPE_2__* channel; } ;
struct TYPE_4__ {int /*<<< orphan*/  target_cpu; } ;

/* Variables and functions */
 int ENOMEM ; 
 int cpu_to_node (int /*<<< orphan*/ ) ; 
 scalar_t__ vzalloc (size_t) ; 
 scalar_t__ vzalloc_node (size_t,int) ; 

int netvsc_alloc_recv_comp_ring(struct netvsc_device *net_device, u32 q_idx)
{
	struct netvsc_channel *nvchan = &net_device->chan_table[q_idx];
	int node = cpu_to_node(nvchan->channel->target_cpu);
	size_t size;

	size = net_device->recv_completion_cnt * sizeof(struct recv_comp_data);
	nvchan->mrc.slots = vzalloc_node(size, node);
	if (!nvchan->mrc.slots)
		nvchan->mrc.slots = vzalloc(size);

	return nvchan->mrc.slots ? 0 : -ENOMEM;
}