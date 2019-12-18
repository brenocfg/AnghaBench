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
struct nvec_msg {short* data; short size; int /*<<< orphan*/  node; } ;
struct nvec_chip {int /*<<< orphan*/  tx_work; int /*<<< orphan*/  tx_lock; int /*<<< orphan*/  tx_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  NVEC_MSG_TX ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (short*,unsigned char const*,short) ; 
 struct nvec_msg* nvec_msg_alloc (struct nvec_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int nvec_write_async(struct nvec_chip *nvec, const unsigned char *data,
		     short size)
{
	struct nvec_msg *msg;
	unsigned long flags;

	msg = nvec_msg_alloc(nvec, NVEC_MSG_TX);

	if (!msg)
		return -ENOMEM;

	msg->data[0] = size;
	memcpy(msg->data + 1, data, size);
	msg->size = size + 1;

	spin_lock_irqsave(&nvec->tx_lock, flags);
	list_add_tail(&msg->node, &nvec->tx_data);
	spin_unlock_irqrestore(&nvec->tx_lock, flags);

	schedule_work(&nvec->tx_work);

	return 0;
}