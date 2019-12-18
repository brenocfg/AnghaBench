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
struct mbox_test_device {void* rx_buffer; int /*<<< orphan*/  async_queue; int /*<<< orphan*/  waitq; int /*<<< orphan*/  lock; scalar_t__ rx_mmio; } ;
struct mbox_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_PREFIX_ADDRESS ; 
 int /*<<< orphan*/  MBOX_MAX_MSG_LEN ; 
 int /*<<< orphan*/  POLL_IN ; 
 int /*<<< orphan*/  SIGIO ; 
 struct mbox_test_device* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kill_fasync (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mbox_data_ready ; 
 int /*<<< orphan*/  memcpy (void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy_fromio (void*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_hex_dump_bytes (char*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mbox_test_receive_message(struct mbox_client *client, void *message)
{
	struct mbox_test_device *tdev = dev_get_drvdata(client->dev);
	unsigned long flags;

	spin_lock_irqsave(&tdev->lock, flags);
	if (tdev->rx_mmio) {
		memcpy_fromio(tdev->rx_buffer, tdev->rx_mmio, MBOX_MAX_MSG_LEN);
		print_hex_dump_bytes("Client: Received [MMIO]: ", DUMP_PREFIX_ADDRESS,
				     tdev->rx_buffer, MBOX_MAX_MSG_LEN);
	} else if (message) {
		print_hex_dump_bytes("Client: Received [API]: ", DUMP_PREFIX_ADDRESS,
				     message, MBOX_MAX_MSG_LEN);
		memcpy(tdev->rx_buffer, message, MBOX_MAX_MSG_LEN);
	}
	mbox_data_ready = true;
	spin_unlock_irqrestore(&tdev->lock, flags);

	wake_up_interruptible(&tdev->waitq);

	kill_fasync(&tdev->async_queue, SIGIO, POLL_IN);
}