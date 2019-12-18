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
struct virtqueue {TYPE_1__* vdev; } ;
struct virtnet_info {struct receive_queue* rq; } ;
struct receive_queue {int /*<<< orphan*/  napi; } ;
struct TYPE_2__ {struct virtnet_info* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  virtqueue_napi_schedule (int /*<<< orphan*/ *,struct virtqueue*) ; 
 size_t vq2rxq (struct virtqueue*) ; 

__attribute__((used)) static void skb_recv_done(struct virtqueue *rvq)
{
	struct virtnet_info *vi = rvq->vdev->priv;
	struct receive_queue *rq = &vi->rq[vq2rxq(rvq)];

	virtqueue_napi_schedule(&rq->napi, rvq);
}