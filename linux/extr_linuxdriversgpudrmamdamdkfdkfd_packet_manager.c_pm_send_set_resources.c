#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct scheduling_resources {int dummy; } ;
struct packet_manager {int /*<<< orphan*/  lock; TYPE_3__* priv_queue; TYPE_1__* pmf; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* rollback_packet ) (TYPE_3__*) ;int /*<<< orphan*/  (* submit_packet ) (TYPE_3__*) ;int /*<<< orphan*/  (* acquire_packet_buffer ) (TYPE_3__*,int,unsigned int**) ;} ;
struct TYPE_8__ {TYPE_2__ ops; } ;
struct TYPE_6__ {int set_resources_size; int (* set_resources ) (struct packet_manager*,int*,struct scheduling_resources*) ;} ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int,unsigned int**) ; 
 int stub2 (struct packet_manager*,int*,struct scheduling_resources*) ; 
 int /*<<< orphan*/  stub3 (TYPE_3__*) ; 
 int /*<<< orphan*/  stub4 (TYPE_3__*) ; 

int pm_send_set_resources(struct packet_manager *pm,
				struct scheduling_resources *res)
{
	uint32_t *buffer, size;
	int retval = 0;

	size = pm->pmf->set_resources_size;
	mutex_lock(&pm->lock);
	pm->priv_queue->ops.acquire_packet_buffer(pm->priv_queue,
					size / sizeof(uint32_t),
					(unsigned int **)&buffer);
	if (!buffer) {
		pr_err("Failed to allocate buffer on kernel queue\n");
		retval = -ENOMEM;
		goto out;
	}

	retval = pm->pmf->set_resources(pm, buffer, res);
	if (!retval)
		pm->priv_queue->ops.submit_packet(pm->priv_queue);
	else
		pm->priv_queue->ops.rollback_packet(pm->priv_queue);

out:
	mutex_unlock(&pm->lock);

	return retval;
}