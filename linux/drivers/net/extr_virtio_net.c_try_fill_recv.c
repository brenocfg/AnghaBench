#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct virtnet_info {scalar_t__ big_packets; scalar_t__ mergeable_rx_bufs; } ;
struct TYPE_4__ {int /*<<< orphan*/  syncp; int /*<<< orphan*/  kicks; } ;
struct receive_queue {TYPE_1__ stats; TYPE_2__* vq; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_5__ {scalar_t__ num_free; } ;

/* Variables and functions */
 int ENOMEM ; 
 int add_recvbuf_big (struct virtnet_info*,struct receive_queue*,int /*<<< orphan*/ ) ; 
 int add_recvbuf_mergeable (struct virtnet_info*,struct receive_queue*,int /*<<< orphan*/ ) ; 
 int add_recvbuf_small (struct virtnet_info*,struct receive_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 
 scalar_t__ virtqueue_kick_prepare (TYPE_2__*) ; 
 scalar_t__ virtqueue_notify (TYPE_2__*) ; 

__attribute__((used)) static bool try_fill_recv(struct virtnet_info *vi, struct receive_queue *rq,
			  gfp_t gfp)
{
	int err;
	bool oom;

	do {
		if (vi->mergeable_rx_bufs)
			err = add_recvbuf_mergeable(vi, rq, gfp);
		else if (vi->big_packets)
			err = add_recvbuf_big(vi, rq, gfp);
		else
			err = add_recvbuf_small(vi, rq, gfp);

		oom = err == -ENOMEM;
		if (err)
			break;
	} while (rq->vq->num_free);
	if (virtqueue_kick_prepare(rq->vq) && virtqueue_notify(rq->vq)) {
		u64_stats_update_begin(&rq->stats.syncp);
		rq->stats.kicks++;
		u64_stats_update_end(&rq->stats.syncp);
	}

	return !oom;
}