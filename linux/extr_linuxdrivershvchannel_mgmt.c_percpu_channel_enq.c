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
struct vmbus_channel {int /*<<< orphan*/  percpu_list; } ;
struct hv_per_cpu_context {int /*<<< orphan*/  chan_list; } ;
struct TYPE_2__ {int /*<<< orphan*/  cpu_context; } ;

/* Variables and functions */
 TYPE_1__ hv_context ; 
 int /*<<< orphan*/  list_add_tail_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct hv_per_cpu_context* this_cpu_ptr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void percpu_channel_enq(void *arg)
{
	struct vmbus_channel *channel = arg;
	struct hv_per_cpu_context *hv_cpu
		= this_cpu_ptr(hv_context.cpu_context);

	list_add_tail_rcu(&channel->percpu_list, &hv_cpu->chan_list);
}