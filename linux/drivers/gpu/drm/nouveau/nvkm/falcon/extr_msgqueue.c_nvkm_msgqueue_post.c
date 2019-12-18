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
struct nvkm_msgqueue_seq {int /*<<< orphan*/  state; struct completion* completion; int /*<<< orphan*/  callback; int /*<<< orphan*/  id; } ;
struct nvkm_msgqueue_queue {int /*<<< orphan*/  state; struct completion* completion; int /*<<< orphan*/  callback; int /*<<< orphan*/  id; } ;
struct nvkm_msgqueue_hdr {int ctrl_flags; int /*<<< orphan*/  seq_id; } ;
struct nvkm_msgqueue {TYPE_1__* func; int /*<<< orphan*/  init_done; } ;
struct completion {int dummy; } ;
typedef  int /*<<< orphan*/  nvkm_msgqueue_callback ;
typedef  enum msgqueue_msg_priority { ____Placeholder_msgqueue_msg_priority } msgqueue_msg_priority ;
struct TYPE_2__ {struct nvkm_msgqueue_seq* (* cmd_queue ) (struct nvkm_msgqueue*,int) ;} ;

/* Variables and functions */
 int CMD_FLAGS_INTR ; 
 int CMD_FLAGS_STATUS ; 
 int ETIMEDOUT ; 
 scalar_t__ IS_ERR (struct nvkm_msgqueue_seq*) ; 
 int PTR_ERR (struct nvkm_msgqueue_seq*) ; 
 int /*<<< orphan*/  SEQ_STATE_PENDING ; 
 int /*<<< orphan*/  SEQ_STATE_USED ; 
 int cmd_write (struct nvkm_msgqueue*,struct nvkm_msgqueue_hdr*,struct nvkm_msgqueue_seq*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 struct nvkm_msgqueue_seq* msgqueue_seq_acquire (struct nvkm_msgqueue*) ; 
 int /*<<< orphan*/  msgqueue_seq_release (struct nvkm_msgqueue*,struct nvkm_msgqueue_seq*) ; 
 struct nvkm_msgqueue_seq* stub1 (struct nvkm_msgqueue*,int) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
nvkm_msgqueue_post(struct nvkm_msgqueue *priv, enum msgqueue_msg_priority prio,
		   struct nvkm_msgqueue_hdr *cmd, nvkm_msgqueue_callback cb,
		   struct completion *completion, bool wait_init)
{
	struct nvkm_msgqueue_seq *seq;
	struct nvkm_msgqueue_queue *queue;
	int ret;

	if (wait_init && !wait_for_completion_timeout(&priv->init_done,
					 msecs_to_jiffies(1000)))
		return -ETIMEDOUT;

	queue = priv->func->cmd_queue(priv, prio);
	if (IS_ERR(queue))
		return PTR_ERR(queue);

	seq = msgqueue_seq_acquire(priv);
	if (IS_ERR(seq))
		return PTR_ERR(seq);

	cmd->seq_id = seq->id;
	cmd->ctrl_flags = CMD_FLAGS_STATUS | CMD_FLAGS_INTR;

	seq->callback = cb;
	seq->state = SEQ_STATE_USED;
	seq->completion = completion;

	ret = cmd_write(priv, cmd, queue);
	if (ret) {
		seq->state = SEQ_STATE_PENDING;
		msgqueue_seq_release(priv, seq);
	}

	return ret;
}