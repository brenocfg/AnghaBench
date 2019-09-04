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
struct hci_dev {int dummy; } ;
struct dtl1_info {int /*<<< orphan*/  lock; struct hci_dev* hdev; TYPE_2__* p_dev; } ;
struct TYPE_4__ {TYPE_1__** resource; } ;
struct TYPE_3__ {unsigned int start; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ UART_IER ; 
 scalar_t__ UART_MCR ; 
 int /*<<< orphan*/  dtl1_hci_close (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_free_dev (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_unregister_dev (struct hci_dev*) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int dtl1_close(struct dtl1_info *info)
{
	unsigned long flags;
	unsigned int iobase = info->p_dev->resource[0]->start;
	struct hci_dev *hdev = info->hdev;

	if (!hdev)
		return -ENODEV;

	dtl1_hci_close(hdev);

	spin_lock_irqsave(&(info->lock), flags);

	/* Reset UART */
	outb(0, iobase + UART_MCR);

	/* Turn off interrupts */
	outb(0, iobase + UART_IER);

	spin_unlock_irqrestore(&(info->lock), flags);

	hci_unregister_dev(hdev);
	hci_free_dev(hdev);

	return 0;
}