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
typedef  int u32 ;
struct mei_msg_hdr {size_t length; int msg_complete; int dma_ring; } ;
struct mei_msg_data {size_t size; void* data; } ;
struct mei_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  device_lock; int /*<<< orphan*/  write_list; int /*<<< orphan*/  write_waiting_list; } ;
struct mei_cl_cb {int blocking; size_t buf_idx; struct mei_msg_data buf; } ;
struct mei_cl {scalar_t__ writing_state; int /*<<< orphan*/  tx_wait; struct mei_device* dev; } ;
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  mei_hdr ;
typedef  int /*<<< orphan*/  dma_len ;

/* Variables and functions */
 size_t EFAULT ; 
 size_t EINPROGRESS ; 
 size_t EINTR ; 
 size_t EINVAL ; 
 size_t ENODEV ; 
 size_t EOVERFLOW ; 
 scalar_t__ MEI_IDLE ; 
 scalar_t__ MEI_WRITE_COMPLETE ; 
 scalar_t__ MEI_WRITING ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  cl_dbg (struct mei_device*,struct mei_cl*,char*,...) ; 
 int /*<<< orphan*/  cl_err (struct mei_device*,struct mei_cl*,char*,size_t) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  mei_cl_is_connected (struct mei_cl*) ; 
 size_t mei_cl_tx_flow_ctrl_creds (struct mei_cl*) ; 
 size_t mei_cl_tx_flow_ctrl_creds_reduce (struct mei_cl*) ; 
 int mei_dma_ring_empty_slots (struct mei_device*) ; 
 int /*<<< orphan*/  mei_dma_ring_write (struct mei_device*,void*,size_t) ; 
 int /*<<< orphan*/  mei_hbuf_acquire (struct mei_device*) ; 
 int mei_hbuf_empty_slots (struct mei_device*) ; 
 int /*<<< orphan*/  mei_io_cb_free (struct mei_cl_cb*) ; 
 int /*<<< orphan*/  mei_msg_hdr_init (struct mei_msg_hdr*,struct mei_cl_cb*) ; 
 size_t mei_slots2data (int) ; 
 int /*<<< orphan*/  mei_tx_cb_enqueue (struct mei_cl_cb*,int /*<<< orphan*/ *) ; 
 size_t mei_write_message (struct mei_device*,struct mei_msg_hdr*,size_t,void const*,size_t) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 size_t pm_runtime_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ ) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 size_t wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

ssize_t mei_cl_write(struct mei_cl *cl, struct mei_cl_cb *cb)
{
	struct mei_device *dev;
	struct mei_msg_data *buf;
	struct mei_msg_hdr mei_hdr;
	size_t hdr_len = sizeof(mei_hdr);
	size_t len, hbuf_len, dr_len;
	int hbuf_slots;
	u32 dr_slots;
	u32 dma_len;
	ssize_t rets;
	bool blocking;
	const void *data;

	if (WARN_ON(!cl || !cl->dev))
		return -ENODEV;

	if (WARN_ON(!cb))
		return -EINVAL;

	dev = cl->dev;

	buf = &cb->buf;
	len = buf->size;

	cl_dbg(dev, cl, "len=%zd\n", len);

	blocking = cb->blocking;
	data = buf->data;

	rets = pm_runtime_get(dev->dev);
	if (rets < 0 && rets != -EINPROGRESS) {
		pm_runtime_put_noidle(dev->dev);
		cl_err(dev, cl, "rpm: get failed %zd\n", rets);
		goto free;
	}

	cb->buf_idx = 0;
	cl->writing_state = MEI_IDLE;


	rets = mei_cl_tx_flow_ctrl_creds(cl);
	if (rets < 0)
		goto err;

	mei_msg_hdr_init(&mei_hdr, cb);

	if (rets == 0) {
		cl_dbg(dev, cl, "No flow control credentials: not sending.\n");
		rets = len;
		goto out;
	}

	if (!mei_hbuf_acquire(dev)) {
		cl_dbg(dev, cl, "Cannot acquire the host buffer: not sending.\n");
		rets = len;
		goto out;
	}

	hbuf_slots = mei_hbuf_empty_slots(dev);
	if (hbuf_slots < 0) {
		rets = -EOVERFLOW;
		goto out;
	}

	hbuf_len = mei_slots2data(hbuf_slots);
	dr_slots = mei_dma_ring_empty_slots(dev);
	dr_len =  mei_slots2data(dr_slots);

	if (len + hdr_len <= hbuf_len) {
		mei_hdr.length = len;
		mei_hdr.msg_complete = 1;
	} else if (dr_slots && hbuf_len >= hdr_len + sizeof(dma_len)) {
		mei_hdr.dma_ring = 1;
		if (len > dr_len)
			len = dr_len;
		else
			mei_hdr.msg_complete = 1;

		mei_hdr.length = sizeof(dma_len);
		dma_len = len;
		data = &dma_len;
	} else {
		len = hbuf_len - hdr_len;
		mei_hdr.length = len;
	}

	if (mei_hdr.dma_ring)
		mei_dma_ring_write(dev, buf->data, len);

	rets = mei_write_message(dev, &mei_hdr, hdr_len,
				 data, mei_hdr.length);
	if (rets)
		goto err;

	rets = mei_cl_tx_flow_ctrl_creds_reduce(cl);
	if (rets)
		goto err;

	cl->writing_state = MEI_WRITING;
	cb->buf_idx = len;
	/* restore return value */
	len = buf->size;

out:
	if (mei_hdr.msg_complete)
		mei_tx_cb_enqueue(cb, &dev->write_waiting_list);
	else
		mei_tx_cb_enqueue(cb, &dev->write_list);

	cb = NULL;
	if (blocking && cl->writing_state != MEI_WRITE_COMPLETE) {

		mutex_unlock(&dev->device_lock);
		rets = wait_event_interruptible(cl->tx_wait,
				cl->writing_state == MEI_WRITE_COMPLETE ||
				(!mei_cl_is_connected(cl)));
		mutex_lock(&dev->device_lock);
		/* wait_event_interruptible returns -ERESTARTSYS */
		if (rets) {
			if (signal_pending(current))
				rets = -EINTR;
			goto err;
		}
		if (cl->writing_state != MEI_WRITE_COMPLETE) {
			rets = -EFAULT;
			goto err;
		}
	}

	rets = len;
err:
	cl_dbg(dev, cl, "rpm: autosuspend\n");
	pm_runtime_mark_last_busy(dev->dev);
	pm_runtime_put_autosuspend(dev->dev);
free:
	mei_io_cb_free(cb);

	return rets;
}