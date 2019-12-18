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
struct st21nfca_i2c_phy {int hard_fault; size_t crc_trials; int /*<<< orphan*/  hdev; int /*<<< orphan*/ * pending_skb; scalar_t__ current_read_len; struct i2c_client* i2c_dev; } ;
struct i2c_client {int irq; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 size_t ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int EAGAIN ; 
 int EBADMSG ; 
 int EIO ; 
 int ENOMEM ; 
 int EREMOTEIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int ST21NFCA_HCI_LLC_MAX_SIZE ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/ * alloc_skb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfc_hci_recv_frame (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int st21nfca_hci_i2c_read (struct st21nfca_i2c_phy*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * wait_tab ; 

__attribute__((used)) static irqreturn_t st21nfca_hci_irq_thread_fn(int irq, void *phy_id)
{
	struct st21nfca_i2c_phy *phy = phy_id;
	struct i2c_client *client;

	int r;

	if (!phy || irq != phy->i2c_dev->irq) {
		WARN_ON_ONCE(1);
		return IRQ_NONE;
	}

	client = phy->i2c_dev;
	dev_dbg(&client->dev, "IRQ\n");

	if (phy->hard_fault != 0)
		return IRQ_HANDLED;

	r = st21nfca_hci_i2c_read(phy, phy->pending_skb);
	if (r == -EREMOTEIO) {
		phy->hard_fault = r;

		nfc_hci_recv_frame(phy->hdev, NULL);

		return IRQ_HANDLED;
	} else if (r == -EAGAIN || r == -EIO) {
		return IRQ_HANDLED;
	} else if (r == -EBADMSG && phy->crc_trials < ARRAY_SIZE(wait_tab)) {
		/*
		 * With ST21NFCA, only one interface (I2C, RF or SWP)
		 * may be active at a time.
		 * Having incorrect crc is usually due to i2c macrocell
		 * deactivation in the middle of a transmission.
		 * It may generate corrupted data on i2c.
		 * We give sometime to get i2c back.
		 * The complete frame will be repeated.
		 */
		msleep(wait_tab[phy->crc_trials]);
		phy->crc_trials++;
		phy->current_read_len = 0;
		kfree_skb(phy->pending_skb);
	} else if (r > 0) {
		/*
		 * We succeeded to read data from the CLF and
		 * data is valid.
		 * Reset counter.
		 */
		nfc_hci_recv_frame(phy->hdev, phy->pending_skb);
		phy->crc_trials = 0;
	} else {
		kfree_skb(phy->pending_skb);
	}

	phy->pending_skb = alloc_skb(ST21NFCA_HCI_LLC_MAX_SIZE * 2, GFP_KERNEL);
	if (phy->pending_skb == NULL) {
		phy->hard_fault = -ENOMEM;
		nfc_hci_recv_frame(phy->hdev, NULL);
	}

	return IRQ_HANDLED;
}