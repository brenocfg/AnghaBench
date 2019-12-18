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
struct cx8802_dev {int /*<<< orphan*/  slock; int /*<<< orphan*/  mpegq; struct cx88_core* core; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MO_TS_DMACNTRL ; 
 int /*<<< orphan*/  MO_TS_GPCNT ; 
 int /*<<< orphan*/  MO_TS_INTMSK ; 
 int /*<<< orphan*/  MO_TS_INTSTAT ; 
 size_t SRAM_CH28 ; 
 int /*<<< orphan*/  cx8802_stop_dma (struct cx8802_dev*) ; 
 int /*<<< orphan*/  cx88_mpeg_irqs ; 
 int /*<<< orphan*/  cx88_print_irqbits (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cx88_sram_channel_dump (struct cx88_core*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cx88_sram_channels ; 
 int /*<<< orphan*/  cx88_wakeup (struct cx88_core*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cx_clear (int /*<<< orphan*/ ,int) ; 
 int cx_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx_write (int /*<<< orphan*/ ,int) ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  dprintk (int,char*,...) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cx8802_mpeg_irq(struct cx8802_dev *dev)
{
	struct cx88_core *core = dev->core;
	u32 status, mask, count;

	dprintk(1, "\n");
	status = cx_read(MO_TS_INTSTAT);
	mask   = cx_read(MO_TS_INTMSK);
	if (0 == (status & mask))
		return;

	cx_write(MO_TS_INTSTAT, status);

	if (debug || (status & mask & ~0xff))
		cx88_print_irqbits("irq mpeg ",
				   cx88_mpeg_irqs, ARRAY_SIZE(cx88_mpeg_irqs),
				   status, mask);

	/* risc op code error */
	if (status & (1 << 16)) {
		pr_warn("mpeg risc op code error\n");
		cx_clear(MO_TS_DMACNTRL, 0x11);
		cx88_sram_channel_dump(dev->core,
				       &cx88_sram_channels[SRAM_CH28]);
	}

	/* risc1 y */
	if (status & 0x01) {
		dprintk(1, "wake up\n");
		spin_lock(&dev->slock);
		count = cx_read(MO_TS_GPCNT);
		cx88_wakeup(dev->core, &dev->mpegq, count);
		spin_unlock(&dev->slock);
	}

	/* other general errors */
	if (status & 0x1f0100) {
		dprintk(0, "general errors: 0x%08x\n", status & 0x1f0100);
		spin_lock(&dev->slock);
		cx8802_stop_dma(dev);
		spin_unlock(&dev->slock);
	}
}