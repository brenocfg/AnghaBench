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
struct nvmet_tcp_queue {int nr_cmds; struct nvmet_tcp_cmd* cmds; } ;
struct nvmet_tcp_cmd {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct nvmet_tcp_cmd* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nvmet_tcp_cmd*) ; 
 int nvmet_tcp_alloc_cmd (struct nvmet_tcp_queue*,struct nvmet_tcp_cmd*) ; 
 int /*<<< orphan*/  nvmet_tcp_free_cmd (struct nvmet_tcp_cmd*) ; 

__attribute__((used)) static int nvmet_tcp_alloc_cmds(struct nvmet_tcp_queue *queue)
{
	struct nvmet_tcp_cmd *cmds;
	int i, ret = -EINVAL, nr_cmds = queue->nr_cmds;

	cmds = kcalloc(nr_cmds, sizeof(struct nvmet_tcp_cmd), GFP_KERNEL);
	if (!cmds)
		goto out;

	for (i = 0; i < nr_cmds; i++) {
		ret = nvmet_tcp_alloc_cmd(queue, cmds + i);
		if (ret)
			goto out_free;
	}

	queue->cmds = cmds;

	return 0;
out_free:
	while (--i >= 0)
		nvmet_tcp_free_cmd(cmds + i);
	kfree(cmds);
out:
	return ret;
}