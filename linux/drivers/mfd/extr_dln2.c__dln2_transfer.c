#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u16 ;
struct dln2_rx_context {TYPE_2__* urb; int /*<<< orphan*/  done; } ;
struct TYPE_6__ {int /*<<< orphan*/  size; } ;
struct dln2_response {int /*<<< orphan*/  result; TYPE_3__ hdr; } ;
struct dln2_mod_rx_slots {struct dln2_rx_context* slots; } ;
struct dln2_dev {int /*<<< orphan*/  disconnect_wq; scalar_t__ disconnect; int /*<<< orphan*/  disconnect_lock; int /*<<< orphan*/  active_transfers; struct dln2_mod_rx_slots* mod_rx_slots; TYPE_1__* interface; } ;
struct device {int dummy; } ;
struct TYPE_5__ {struct dln2_response* transfer_buffer; } ;
struct TYPE_4__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLN2_USB_TIMEOUT ; 
 int ENODEV ; 
 int EPROTO ; 
 int EREMOTEIO ; 
 int ETIMEDOUT ; 
 int alloc_rx_slot (struct dln2_dev*,size_t) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,size_t,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int dln2_send_wait (struct dln2_dev*,size_t,size_t,int,void const*,unsigned int) ; 
 int /*<<< orphan*/  free_rx_slot (struct dln2_dev*,size_t,int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,struct dln2_response*,unsigned int) ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int wait_for_completion_interruptible_timeout (int /*<<< orphan*/ *,unsigned long const) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int _dln2_transfer(struct dln2_dev *dln2, u16 handle, u16 cmd,
			  const void *obuf, unsigned obuf_len,
			  void *ibuf, unsigned *ibuf_len)
{
	int ret = 0;
	int rx_slot;
	struct dln2_response *rsp;
	struct dln2_rx_context *rxc;
	struct device *dev = &dln2->interface->dev;
	const unsigned long timeout = msecs_to_jiffies(DLN2_USB_TIMEOUT);
	struct dln2_mod_rx_slots *rxs = &dln2->mod_rx_slots[handle];
	int size;

	spin_lock(&dln2->disconnect_lock);
	if (!dln2->disconnect)
		dln2->active_transfers++;
	else
		ret = -ENODEV;
	spin_unlock(&dln2->disconnect_lock);

	if (ret)
		return ret;

	rx_slot = alloc_rx_slot(dln2, handle);
	if (rx_slot < 0) {
		ret = rx_slot;
		goto out_decr;
	}

	ret = dln2_send_wait(dln2, handle, cmd, rx_slot, obuf, obuf_len);
	if (ret < 0) {
		dev_err(dev, "USB write failed: %d\n", ret);
		goto out_free_rx_slot;
	}

	rxc = &rxs->slots[rx_slot];

	ret = wait_for_completion_interruptible_timeout(&rxc->done, timeout);
	if (ret <= 0) {
		if (!ret)
			ret = -ETIMEDOUT;
		goto out_free_rx_slot;
	} else {
		ret = 0;
	}

	if (dln2->disconnect) {
		ret = -ENODEV;
		goto out_free_rx_slot;
	}

	/* if we got here we know that the response header has been checked */
	rsp = rxc->urb->transfer_buffer;
	size = le16_to_cpu(rsp->hdr.size);

	if (size < sizeof(*rsp)) {
		ret = -EPROTO;
		goto out_free_rx_slot;
	}

	if (le16_to_cpu(rsp->result) > 0x80) {
		dev_dbg(dev, "%d received response with error %d\n",
			handle, le16_to_cpu(rsp->result));
		ret = -EREMOTEIO;
		goto out_free_rx_slot;
	}

	if (!ibuf)
		goto out_free_rx_slot;

	if (*ibuf_len > size - sizeof(*rsp))
		*ibuf_len = size - sizeof(*rsp);

	memcpy(ibuf, rsp + 1, *ibuf_len);

out_free_rx_slot:
	free_rx_slot(dln2, handle, rx_slot);
out_decr:
	spin_lock(&dln2->disconnect_lock);
	dln2->active_transfers--;
	spin_unlock(&dln2->disconnect_lock);
	if (dln2->disconnect)
		wake_up(&dln2->disconnect_wq);

	return ret;
}