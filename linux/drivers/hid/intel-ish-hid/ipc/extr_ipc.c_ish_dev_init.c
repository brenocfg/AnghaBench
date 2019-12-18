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
struct wr_msg_ctl_info {int /*<<< orphan*/  link; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct ishtp_msg_hdr {int dummy; } ;
struct ishtp_device {scalar_t__ mtu; int /*<<< orphan*/ * devc; int /*<<< orphan*/ * ops; int /*<<< orphan*/  wr_free_list; int /*<<< orphan*/  wr_processing_list; int /*<<< orphan*/  wr_processing_spinlock; int /*<<< orphan*/  wait_hw_ready; } ;
struct ish_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IPC_PAYLOAD_SIZE ; 
 int IPC_TX_FIFO_SIZE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 void* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ish_hw_ops ; 
 int /*<<< orphan*/  ishtp_device_init (struct ishtp_device*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct ishtp_device *ish_dev_init(struct pci_dev *pdev)
{
	struct ishtp_device *dev;
	int	i;

	dev = devm_kzalloc(&pdev->dev,
			   sizeof(struct ishtp_device) + sizeof(struct ish_hw),
			   GFP_KERNEL);
	if (!dev)
		return NULL;

	ishtp_device_init(dev);

	init_waitqueue_head(&dev->wait_hw_ready);

	spin_lock_init(&dev->wr_processing_spinlock);

	/* Init IPC processing and free lists */
	INIT_LIST_HEAD(&dev->wr_processing_list);
	INIT_LIST_HEAD(&dev->wr_free_list);
	for (i = 0; i < IPC_TX_FIFO_SIZE; i++) {
		struct wr_msg_ctl_info	*tx_buf;

		tx_buf = devm_kzalloc(&pdev->dev,
				      sizeof(struct wr_msg_ctl_info),
				      GFP_KERNEL);
		if (!tx_buf) {
			/*
			 * IPC buffers may be limited or not available
			 * at all - although this shouldn't happen
			 */
			dev_err(dev->devc,
				"[ishtp-ish]: failure in Tx FIFO allocations (%d)\n",
				i);
			break;
		}
		list_add_tail(&tx_buf->link, &dev->wr_free_list);
	}

	dev->ops = &ish_hw_ops;
	dev->devc = &pdev->dev;
	dev->mtu = IPC_PAYLOAD_SIZE - sizeof(struct ishtp_msg_hdr);
	return dev;
}