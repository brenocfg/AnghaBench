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
struct virtproc_info {int /*<<< orphan*/  rvq; } ;
struct rpmsg_hdr {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; struct virtproc_info* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (struct device*,char*,unsigned int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int rpmsg_recv_single (struct virtproc_info*,struct device*,struct rpmsg_hdr*,unsigned int) ; 
 struct rpmsg_hdr* virtqueue_get_buf (struct virtqueue*,unsigned int*) ; 
 int /*<<< orphan*/  virtqueue_kick (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rpmsg_recv_done(struct virtqueue *rvq)
{
	struct virtproc_info *vrp = rvq->vdev->priv;
	struct device *dev = &rvq->vdev->dev;
	struct rpmsg_hdr *msg;
	unsigned int len, msgs_received = 0;
	int err;

	msg = virtqueue_get_buf(rvq, &len);
	if (!msg) {
		dev_err(dev, "uhm, incoming signal, but no used buffer ?\n");
		return;
	}

	while (msg) {
		err = rpmsg_recv_single(vrp, dev, msg, len);
		if (err)
			break;

		msgs_received++;

		msg = virtqueue_get_buf(rvq, &len);
	}

	dev_dbg(dev, "Received %u messages\n", msgs_received);

	/* tell the remote processor we added another available rx buffer */
	if (msgs_received)
		virtqueue_kick(vrp->rvq);
}