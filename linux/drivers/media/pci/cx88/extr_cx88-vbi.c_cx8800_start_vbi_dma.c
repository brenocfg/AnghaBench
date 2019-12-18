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
struct cx88_dmaqueue {scalar_t__ count; } ;
struct cx88_core {int pci_irqmask; } ;
struct TYPE_2__ {int /*<<< orphan*/  dma; } ;
struct cx88_buffer {TYPE_1__ risc; } ;
struct cx8800_dev {struct cx88_core* core; } ;

/* Variables and functions */
 int GP_COUNT_CONTROL_RESET ; 
 int /*<<< orphan*/  MO_DEV_CNTRL2 ; 
 int /*<<< orphan*/  MO_PCI_INTMSK ; 
 int /*<<< orphan*/  MO_VBI_GPCNTRL ; 
 int /*<<< orphan*/  MO_VBOS_CONTROL ; 
 int /*<<< orphan*/  MO_VID_DMACNTRL ; 
 int /*<<< orphan*/  MO_VID_INTMSK ; 
 int PCI_INT_VIDINT ; 
 size_t SRAM_CH24 ; 
 int /*<<< orphan*/  VBI_LINE_LENGTH ; 
 int /*<<< orphan*/  VID_CAPTURE_CONTROL ; 
 int /*<<< orphan*/  cx88_sram_channel_setup (struct cx88_core*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cx88_sram_channels ; 
 int /*<<< orphan*/  cx_set (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cx_write (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int cx8800_start_vbi_dma(struct cx8800_dev    *dev,
				struct cx88_dmaqueue *q,
				struct cx88_buffer   *buf)
{
	struct cx88_core *core = dev->core;

	/* setup fifo + format */
	cx88_sram_channel_setup(dev->core, &cx88_sram_channels[SRAM_CH24],
				VBI_LINE_LENGTH, buf->risc.dma);

	cx_write(MO_VBOS_CONTROL, (1 << 18) |  /* comb filter delay fixup */
				  (1 << 15) |  /* enable vbi capture */
				  (1 << 11));

	/* reset counter */
	cx_write(MO_VBI_GPCNTRL, GP_COUNT_CONTROL_RESET);
	q->count = 0;

	/* enable irqs */
	cx_set(MO_PCI_INTMSK, core->pci_irqmask | PCI_INT_VIDINT);
	cx_set(MO_VID_INTMSK, 0x0f0088);

	/* enable capture */
	cx_set(VID_CAPTURE_CONTROL, 0x18);

	/* start dma */
	cx_set(MO_DEV_CNTRL2, (1 << 5));
	cx_set(MO_VID_DMACNTRL, 0x88);

	return 0;
}