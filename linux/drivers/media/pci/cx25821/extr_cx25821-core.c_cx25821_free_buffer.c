#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cx25821_dev {int /*<<< orphan*/  pci; } ;
struct TYPE_2__ {scalar_t__ size; int /*<<< orphan*/  dma; int /*<<< orphan*/  cpu; } ;
struct cx25821_buffer {TYPE_1__ risc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  in_interrupt () ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void cx25821_free_buffer(struct cx25821_dev *dev, struct cx25821_buffer *buf)
{
	BUG_ON(in_interrupt());
	if (WARN_ON(buf->risc.size == 0))
		return;
	pci_free_consistent(dev->pci,
			buf->risc.size, buf->risc.cpu, buf->risc.dma);
	memset(&buf->risc, 0, sizeof(buf->risc));
}