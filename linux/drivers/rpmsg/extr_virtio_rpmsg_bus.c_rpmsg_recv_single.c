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
struct virtproc_info {unsigned int buf_size; int /*<<< orphan*/  rvq; int /*<<< orphan*/  endpoints_lock; int /*<<< orphan*/  endpoints; } ;
struct scatterlist {int dummy; } ;
struct rpmsg_hdr {unsigned int len; int /*<<< orphan*/  src; int /*<<< orphan*/  data; int /*<<< orphan*/  dst; int /*<<< orphan*/  reserved; int /*<<< orphan*/  flags; } ;
struct rpmsg_endpoint {int /*<<< orphan*/  refcount; int /*<<< orphan*/  cb_lock; int /*<<< orphan*/  priv; int /*<<< orphan*/  rpdev; int /*<<< orphan*/  (* cb ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_PREFIX_NONE ; 
 int EINVAL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  __ept_release ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,...) ; 
 int /*<<< orphan*/  dynamic_hex_dump (char*,int /*<<< orphan*/ ,int,int,struct rpmsg_hdr*,int /*<<< orphan*/ ,int) ; 
 struct rpmsg_endpoint* idr_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpmsg_sg_init (struct scatterlist*,struct rpmsg_hdr*,unsigned int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int virtqueue_add_inbuf (int /*<<< orphan*/ ,struct scatterlist*,int,struct rpmsg_hdr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rpmsg_recv_single(struct virtproc_info *vrp, struct device *dev,
			     struct rpmsg_hdr *msg, unsigned int len)
{
	struct rpmsg_endpoint *ept;
	struct scatterlist sg;
	int err;

	dev_dbg(dev, "From: 0x%x, To: 0x%x, Len: %d, Flags: %d, Reserved: %d\n",
		msg->src, msg->dst, msg->len, msg->flags, msg->reserved);
#if defined(CONFIG_DYNAMIC_DEBUG)
	dynamic_hex_dump("rpmsg_virtio RX: ", DUMP_PREFIX_NONE, 16, 1,
			 msg, sizeof(*msg) + msg->len, true);
#endif

	/*
	 * We currently use fixed-sized buffers, so trivially sanitize
	 * the reported payload length.
	 */
	if (len > vrp->buf_size ||
	    msg->len > (len - sizeof(struct rpmsg_hdr))) {
		dev_warn(dev, "inbound msg too big: (%d, %d)\n", len, msg->len);
		return -EINVAL;
	}

	/* use the dst addr to fetch the callback of the appropriate user */
	mutex_lock(&vrp->endpoints_lock);

	ept = idr_find(&vrp->endpoints, msg->dst);

	/* let's make sure no one deallocates ept while we use it */
	if (ept)
		kref_get(&ept->refcount);

	mutex_unlock(&vrp->endpoints_lock);

	if (ept) {
		/* make sure ept->cb doesn't go away while we use it */
		mutex_lock(&ept->cb_lock);

		if (ept->cb)
			ept->cb(ept->rpdev, msg->data, msg->len, ept->priv,
				msg->src);

		mutex_unlock(&ept->cb_lock);

		/* farewell, ept, we don't need you anymore */
		kref_put(&ept->refcount, __ept_release);
	} else
		dev_warn(dev, "msg received with no recipient\n");

	/* publish the real size of the buffer */
	rpmsg_sg_init(&sg, msg, vrp->buf_size);

	/* add the buffer back to the remote processor's virtqueue */
	err = virtqueue_add_inbuf(vrp->rvq, &sg, 1, msg, GFP_KERNEL);
	if (err < 0) {
		dev_err(dev, "failed to add a virtqueue buffer: %d\n", err);
		return err;
	}

	return 0;
}