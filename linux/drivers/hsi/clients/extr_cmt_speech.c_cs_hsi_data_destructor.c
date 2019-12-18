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
struct hsi_msg {scalar_t__ ttype; int /*<<< orphan*/  status; struct cs_hsi_iface* context; } ;
struct cs_hsi_iface {scalar_t__ iface_state; int data_state; int /*<<< orphan*/  lock; int /*<<< orphan*/  datawait; } ;
struct TYPE_4__ {TYPE_1__* cl; } ;
struct TYPE_3__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 scalar_t__ CS_STATE_CLOSED ; 
 scalar_t__ HSI_MSG_READ ; 
 int /*<<< orphan*/  HSI_STATUS_COMPLETED ; 
 int SSI_CHANNEL_STATE_POLL ; 
 int SSI_CHANNEL_STATE_READING ; 
 int SSI_CHANNEL_STATE_WRITING ; 
 TYPE_2__ cs_char_data ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  waitqueue_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cs_hsi_data_destructor(struct hsi_msg *msg)
{
	struct cs_hsi_iface *hi = msg->context;
	const char *dir = (msg->ttype == HSI_MSG_READ) ? "TX" : "RX";

	dev_dbg(&cs_char_data.cl->device, "Freeing data %s message\n", dir);

	spin_lock(&hi->lock);
	if (hi->iface_state != CS_STATE_CLOSED)
		dev_err(&cs_char_data.cl->device,
				"Data %s flush while device active\n", dir);
	if (msg->ttype == HSI_MSG_READ)
		hi->data_state &=
			~(SSI_CHANNEL_STATE_POLL | SSI_CHANNEL_STATE_READING);
	else
		hi->data_state &= ~SSI_CHANNEL_STATE_WRITING;

	msg->status = HSI_STATUS_COMPLETED;
	if (unlikely(waitqueue_active(&hi->datawait)))
		wake_up_interruptible(&hi->datawait);

	spin_unlock(&hi->lock);
}