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
struct cx88_audio_dev {int /*<<< orphan*/  substream; int /*<<< orphan*/  count; struct cx88_core* core; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int AUD_INT_DN_RISCI1 ; 
 int AUD_INT_DN_SYNC ; 
 int AUD_INT_OPC_ERR ; 
 int GP_COUNT_CONTROL_RESET ; 
 int /*<<< orphan*/  MO_AUDD_GPCNT ; 
 int /*<<< orphan*/  MO_AUDD_GPCNTRL ; 
 int /*<<< orphan*/  MO_AUD_DMACNTRL ; 
 int /*<<< orphan*/  MO_AUD_INTMSK ; 
 int /*<<< orphan*/  MO_AUD_INTSTAT ; 
 size_t SRAM_CH25 ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cx88_aud_irqs ; 
 int /*<<< orphan*/  cx88_print_irqbits (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cx88_sram_channel_dump (struct cx88_core*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cx88_sram_channels ; 
 int /*<<< orphan*/  cx_clear (int /*<<< orphan*/ ,int) ; 
 int cx_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx_write (int /*<<< orphan*/ ,int) ; 
 int debug ; 
 int /*<<< orphan*/  dprintk (int,char*) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  snd_pcm_period_elapsed (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cx8801_aud_irq(struct cx88_audio_dev *chip)
{
	struct cx88_core *core = chip->core;
	u32 status, mask;

	status = cx_read(MO_AUD_INTSTAT);
	mask   = cx_read(MO_AUD_INTMSK);
	if (0 == (status & mask))
		return;
	cx_write(MO_AUD_INTSTAT, status);
	if (debug > 1  ||  (status & mask & ~0xff))
		cx88_print_irqbits("irq aud",
				   cx88_aud_irqs, ARRAY_SIZE(cx88_aud_irqs),
				   status, mask);
	/* risc op code error */
	if (status & AUD_INT_OPC_ERR) {
		pr_warn("Audio risc op code error\n");
		cx_clear(MO_AUD_DMACNTRL, 0x11);
		cx88_sram_channel_dump(core, &cx88_sram_channels[SRAM_CH25]);
	}
	if (status & AUD_INT_DN_SYNC) {
		dprintk(1, "Downstream sync error\n");
		cx_write(MO_AUDD_GPCNTRL, GP_COUNT_CONTROL_RESET);
		return;
	}
	/* risc1 downstream */
	if (status & AUD_INT_DN_RISCI1) {
		atomic_set(&chip->count, cx_read(MO_AUDD_GPCNT));
		snd_pcm_period_elapsed(chip->substream);
	}
	/* FIXME: Any other status should deserve a special handling? */
}