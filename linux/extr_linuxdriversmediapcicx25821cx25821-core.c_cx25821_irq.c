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
typedef  int u32 ;
struct cx25821_dev {TYPE_2__* channels; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {TYPE_1__* sram_channels; } ;
struct TYPE_3__ {int /*<<< orphan*/  int_stat; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_RETVAL (int) ; 
 int /*<<< orphan*/  PCI_INT_STAT ; 
 int VID_CHANNEL_NUM ; 
 scalar_t__ cx25821_video_irq (struct cx25821_dev*,int,int) ; 
 int cx_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx_write (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static irqreturn_t cx25821_irq(int irq, void *dev_id)
{
	struct cx25821_dev *dev = dev_id;
	u32 pci_status;
	u32 vid_status;
	int i, handled = 0;
	u32 mask[8] = { 1, 2, 4, 8, 16, 32, 64, 128 };

	pci_status = cx_read(PCI_INT_STAT);

	if (pci_status == 0)
		goto out;

	for (i = 0; i < VID_CHANNEL_NUM; i++) {
		if (pci_status & mask[i]) {
			vid_status = cx_read(dev->channels[i].
				sram_channels->int_stat);

			if (vid_status)
				handled += cx25821_video_irq(dev, i,
						vid_status);

			cx_write(PCI_INT_STAT, mask[i]);
		}
	}

out:
	return IRQ_RETVAL(handled);
}