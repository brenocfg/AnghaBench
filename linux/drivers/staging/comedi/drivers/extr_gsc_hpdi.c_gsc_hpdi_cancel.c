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
struct comedi_subdevice {int dummy; } ;
struct comedi_device {scalar_t__ mmio; } ;

/* Variables and functions */
 scalar_t__ BOARD_CONTROL_REG ; 
 scalar_t__ INTERRUPT_CONTROL_REG ; 
 int /*<<< orphan*/  gsc_hpdi_abort_dma (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int gsc_hpdi_cancel(struct comedi_device *dev,
			   struct comedi_subdevice *s)
{
	writel(0, dev->mmio + BOARD_CONTROL_REG);
	writel(0, dev->mmio + INTERRUPT_CONTROL_REG);

	gsc_hpdi_abort_dma(dev, 0);

	return 0;
}