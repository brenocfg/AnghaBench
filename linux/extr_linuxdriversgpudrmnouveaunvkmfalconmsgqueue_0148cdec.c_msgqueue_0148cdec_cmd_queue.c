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
struct nvkm_msgqueue_queue {int dummy; } ;
struct nvkm_msgqueue {int dummy; } ;
struct msgqueue_0148cdec {struct nvkm_msgqueue_queue* queue; } ;
typedef  enum msgqueue_msg_priority { ____Placeholder_msgqueue_msg_priority } msgqueue_msg_priority ;

/* Variables and functions */
 size_t MSGQUEUE_0148CDEC_COMMAND_QUEUE ; 
 struct msgqueue_0148cdec* msgqueue_0148cdec (struct nvkm_msgqueue*) ; 

__attribute__((used)) static struct nvkm_msgqueue_queue *
msgqueue_0148cdec_cmd_queue(struct nvkm_msgqueue *queue,
			    enum msgqueue_msg_priority priority)
{
	struct msgqueue_0148cdec *priv = msgqueue_0148cdec(queue);

	return &priv->queue[MSGQUEUE_0148CDEC_COMMAND_QUEUE];
}