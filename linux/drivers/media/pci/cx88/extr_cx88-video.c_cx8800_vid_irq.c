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
typedef  int u32 ;
struct cx88_core {int dummy; } ;
struct cx8800_dev {int /*<<< orphan*/  slock; int /*<<< orphan*/  vbiq; int /*<<< orphan*/  vidq; struct cx88_core* core; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MO_VBI_GPCNT ; 
 int /*<<< orphan*/  MO_VIDY_GPCNT ; 
 int /*<<< orphan*/  MO_VID_DMACNTRL ; 
 int /*<<< orphan*/  MO_VID_INTMSK ; 
 int /*<<< orphan*/  MO_VID_INTSTAT ; 
 size_t SRAM_CH21 ; 
 int /*<<< orphan*/  VID_CAPTURE_CONTROL ; 
 int /*<<< orphan*/  cx88_print_irqbits (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cx88_sram_channel_dump (struct cx88_core*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cx88_sram_channels ; 
 int /*<<< orphan*/  cx88_vid_irqs ; 
 int /*<<< orphan*/  cx88_wakeup (struct cx88_core*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cx_clear (int /*<<< orphan*/ ,int) ; 
 int cx_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx_write (int /*<<< orphan*/ ,int) ; 
 scalar_t__ irq_debug ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cx8800_vid_irq(struct cx8800_dev *dev)
{
	struct cx88_core *core = dev->core;
	u32 status, mask, count;

	status = cx_read(MO_VID_INTSTAT);
	mask   = cx_read(MO_VID_INTMSK);
	if (0 == (status & mask))
		return;
	cx_write(MO_VID_INTSTAT, status);
	if (irq_debug  ||  (status & mask & ~0xff))
		cx88_print_irqbits("irq vid",
				   cx88_vid_irqs, ARRAY_SIZE(cx88_vid_irqs),
				   status, mask);

	/* risc op code error */
	if (status & (1 << 16)) {
		pr_warn("video risc op code error\n");
		cx_clear(MO_VID_DMACNTRL, 0x11);
		cx_clear(VID_CAPTURE_CONTROL, 0x06);
		cx88_sram_channel_dump(core, &cx88_sram_channels[SRAM_CH21]);
	}

	/* risc1 y */
	if (status & 0x01) {
		spin_lock(&dev->slock);
		count = cx_read(MO_VIDY_GPCNT);
		cx88_wakeup(core, &dev->vidq, count);
		spin_unlock(&dev->slock);
	}

	/* risc1 vbi */
	if (status & 0x08) {
		spin_lock(&dev->slock);
		count = cx_read(MO_VBI_GPCNT);
		cx88_wakeup(core, &dev->vbiq, count);
		spin_unlock(&dev->slock);
	}
}