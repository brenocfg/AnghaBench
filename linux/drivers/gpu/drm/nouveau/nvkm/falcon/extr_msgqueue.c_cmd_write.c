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
struct nvkm_subdev {int dummy; } ;
struct nvkm_msgqueue_queue {int dummy; } ;
struct nvkm_msgqueue_hdr {int /*<<< orphan*/  size; } ;
struct nvkm_msgqueue {TYPE_1__* falcon; } ;
struct TYPE_2__ {struct nvkm_subdev* owner; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  cmd_queue_close (struct nvkm_msgqueue*,struct nvkm_msgqueue_queue*,int) ; 
 int cmd_queue_open (struct nvkm_msgqueue*,struct nvkm_msgqueue_queue*,int /*<<< orphan*/ ) ; 
 int cmd_queue_push (struct nvkm_msgqueue*,struct nvkm_msgqueue_queue*,struct nvkm_msgqueue_hdr*,int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (unsigned int) ; 
 int /*<<< orphan*/  nvkm_error (struct nvkm_subdev const*,char*) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static int
cmd_write(struct nvkm_msgqueue *priv, struct nvkm_msgqueue_hdr *cmd,
	  struct nvkm_msgqueue_queue *queue)
{
	const struct nvkm_subdev *subdev = priv->falcon->owner;
	static unsigned timeout = 2000;
	unsigned long end_jiffies = jiffies + msecs_to_jiffies(timeout);
	int ret = -EAGAIN;
	bool commit = true;

	while (ret == -EAGAIN && time_before(jiffies, end_jiffies))
		ret = cmd_queue_open(priv, queue, cmd->size);
	if (ret) {
		nvkm_error(subdev, "pmu_queue_open_write failed\n");
		return ret;
	}

	ret = cmd_queue_push(priv, queue, cmd, cmd->size);
	if (ret) {
		nvkm_error(subdev, "pmu_queue_push failed\n");
		commit = false;
	}

	cmd_queue_close(priv, queue, commit);

	return ret;
}