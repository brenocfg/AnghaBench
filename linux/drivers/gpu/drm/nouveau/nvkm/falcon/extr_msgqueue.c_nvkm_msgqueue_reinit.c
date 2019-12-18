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
struct nvkm_msgqueue {int init_msg_received; int /*<<< orphan*/  init_done; } ;

/* Variables and functions */
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 

int
nvkm_msgqueue_reinit(struct nvkm_msgqueue *queue)
{
	/* firmware not set yet... */
	if (!queue)
		return 0;

	queue->init_msg_received = false;
	reinit_completion(&queue->init_done);

	return 0;
}