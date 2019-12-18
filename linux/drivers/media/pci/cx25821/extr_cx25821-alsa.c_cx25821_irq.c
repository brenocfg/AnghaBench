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
typedef  scalar_t__ u32 ;
struct cx25821_dev {int dummy; } ;
struct cx25821_audio_dev {struct cx25821_dev* dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUD_A_INT_MSK ; 
 int /*<<< orphan*/  AUD_A_INT_STAT ; 
 int /*<<< orphan*/  IRQ_RETVAL (int) ; 
 int /*<<< orphan*/  PCI_INT_STAT ; 
 int /*<<< orphan*/  cx25821_aud_irq (struct cx25821_audio_dev*,scalar_t__,scalar_t__) ; 
 scalar_t__ cx_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx_write (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static irqreturn_t cx25821_irq(int irq, void *dev_id)
{
	struct cx25821_audio_dev *chip = dev_id;
	struct cx25821_dev *dev = chip->dev;
	u32 status, pci_status;
	u32 audint_status, audint_mask;
	int loop, handled = 0;

	audint_status = cx_read(AUD_A_INT_STAT);
	audint_mask = cx_read(AUD_A_INT_MSK);
	status = cx_read(PCI_INT_STAT);

	for (loop = 0; loop < 1; loop++) {
		status = cx_read(PCI_INT_STAT);
		if (0 == status) {
			status = cx_read(PCI_INT_STAT);
			audint_status = cx_read(AUD_A_INT_STAT);
			audint_mask = cx_read(AUD_A_INT_MSK);

			if (status) {
				handled = 1;
				cx_write(PCI_INT_STAT, status);

				cx25821_aud_irq(chip, audint_status,
						audint_mask);
				break;
			} else {
				goto out;
			}
		}

		handled = 1;
		cx_write(PCI_INT_STAT, status);

		cx25821_aud_irq(chip, audint_status, audint_mask);
	}

	pci_status = cx_read(PCI_INT_STAT);

	if (handled)
		cx_write(PCI_INT_STAT, pci_status);

out:
	return IRQ_RETVAL(handled);
}