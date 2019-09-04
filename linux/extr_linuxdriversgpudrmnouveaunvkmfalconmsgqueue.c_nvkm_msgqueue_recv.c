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
struct nvkm_subdev {int dummy; } ;
struct nvkm_msgqueue {TYPE_2__* func; TYPE_1__* falcon; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* recv ) (struct nvkm_msgqueue*) ;} ;
struct TYPE_3__ {struct nvkm_subdev* owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_warn (struct nvkm_subdev const*,char*) ; 
 int /*<<< orphan*/  stub1 (struct nvkm_msgqueue*) ; 

void
nvkm_msgqueue_recv(struct nvkm_msgqueue *queue)
{
	if (!queue->func || !queue->func->recv) {
		const struct nvkm_subdev *subdev = queue->falcon->owner;

		nvkm_warn(subdev, "missing msgqueue recv function\n");
		return;
	}

	queue->func->recv(queue);
}