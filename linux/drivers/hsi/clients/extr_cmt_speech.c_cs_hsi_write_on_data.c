#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int /*<<< orphan*/  sgl; } ;
struct hsi_msg {int /*<<< orphan*/  complete; TYPE_1__ sgt; } ;
struct cs_hsi_iface {scalar_t__ iface_state; int data_state; unsigned int tx_slot; struct hsi_msg* data_tx_msg; int /*<<< orphan*/  lock; TYPE_2__* cl; int /*<<< orphan*/  buf_size; scalar_t__* tx_offsets; scalar_t__ mmap_base; } ;
struct TYPE_4__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 scalar_t__ CS_STATE_CONFIGURED ; 
 int EBUSY ; 
 int EINVAL ; 
 int EIO ; 
 int SSI_CHANNEL_STATE_ERROR ; 
 int SSI_CHANNEL_STATE_WRITING ; 
 int /*<<< orphan*/  cs_hsi_data_write_error (struct cs_hsi_iface*,struct hsi_msg*) ; 
 int /*<<< orphan*/  cs_hsi_write_on_data_complete ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int hsi_async_write (TYPE_2__*,struct hsi_msg*) ; 
 int /*<<< orphan*/  sg_init_one (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cs_hsi_write_on_data(struct cs_hsi_iface *hi, unsigned int slot)
{
	u32 *address;
	struct hsi_msg *txmsg;
	int ret;

	spin_lock(&hi->lock);
	if (hi->iface_state != CS_STATE_CONFIGURED) {
		dev_err(&hi->cl->device, "Not configured, aborting\n");
		ret = -EINVAL;
		goto error;
	}
	if (hi->data_state & SSI_CHANNEL_STATE_ERROR) {
		dev_err(&hi->cl->device, "HSI error, aborting\n");
		ret = -EIO;
		goto error;
	}
	if (hi->data_state & SSI_CHANNEL_STATE_WRITING) {
		dev_err(&hi->cl->device, "Write pending on data channel.\n");
		ret = -EBUSY;
		goto error;
	}
	hi->data_state |= SSI_CHANNEL_STATE_WRITING;
	spin_unlock(&hi->lock);

	hi->tx_slot = slot;
	address = (u32 *)(hi->mmap_base + hi->tx_offsets[hi->tx_slot]);
	txmsg = hi->data_tx_msg;
	sg_init_one(txmsg->sgt.sgl, address, hi->buf_size);
	txmsg->complete = cs_hsi_write_on_data_complete;
	ret = hsi_async_write(hi->cl, txmsg);
	if (ret)
		cs_hsi_data_write_error(hi, txmsg);

	return ret;

error:
	spin_unlock(&hi->lock);
	if (ret == -EIO)
		cs_hsi_data_write_error(hi, hi->data_tx_msg);

	return ret;
}