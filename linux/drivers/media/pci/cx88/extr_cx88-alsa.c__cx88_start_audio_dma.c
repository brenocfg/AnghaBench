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
struct sram_channel {scalar_t__ cmds_start; } ;
struct cx88_core {int pci_irqmask; } ;
struct cx88_audio_dev {int num_periods; struct cx88_core* core; int /*<<< orphan*/  count; struct cx88_audio_buffer* buf; } ;
struct TYPE_2__ {int /*<<< orphan*/  dma; } ;
struct cx88_audio_buffer {int bpl; TYPE_1__ risc; } ;

/* Variables and functions */
 int AUD_INT_DN_RISCI1 ; 
 int AUD_INT_DN_RISCI2 ; 
 int AUD_INT_DN_SYNC ; 
 int AUD_INT_OPC_ERR ; 
 int GP_COUNT_CONTROL_RESET ; 
 int /*<<< orphan*/  MO_AUDD_GPCNTRL ; 
 int /*<<< orphan*/  MO_AUDD_LNGTH ; 
 int /*<<< orphan*/  MO_AUD_DMACNTRL ; 
 int /*<<< orphan*/  MO_AUD_INTMSK ; 
 int /*<<< orphan*/  MO_AUD_INTSTAT ; 
 int /*<<< orphan*/  MO_DEV_CNTRL2 ; 
 int /*<<< orphan*/  MO_PCI_INTMSK ; 
 int PCI_INT_AUDINT ; 
 size_t SRAM_CH25 ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx88_sram_channel_dump (struct cx88_core*,struct sram_channel const*) ; 
 int /*<<< orphan*/  cx88_sram_channel_setup (struct cx88_core*,struct sram_channel const*,int,int /*<<< orphan*/ ) ; 
 struct sram_channel* cx88_sram_channels ; 
 int /*<<< orphan*/  cx_clear (int /*<<< orphan*/ ,int) ; 
 int cx_read (scalar_t__) ; 
 int /*<<< orphan*/  cx_set (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cx_write (int /*<<< orphan*/ ,int) ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  dprintk (int,char*,int,int,int,int) ; 

__attribute__((used)) static int _cx88_start_audio_dma(struct cx88_audio_dev *chip)
{
	struct cx88_audio_buffer *buf = chip->buf;
	struct cx88_core *core = chip->core;
	const struct sram_channel *audio_ch = &cx88_sram_channels[SRAM_CH25];

	/* Make sure RISC/FIFO are off before changing FIFO/RISC settings */
	cx_clear(MO_AUD_DMACNTRL, 0x11);

	/* setup fifo + format - out channel */
	cx88_sram_channel_setup(chip->core, audio_ch, buf->bpl, buf->risc.dma);

	/* sets bpl size */
	cx_write(MO_AUDD_LNGTH, buf->bpl);

	/* reset counter */
	cx_write(MO_AUDD_GPCNTRL, GP_COUNT_CONTROL_RESET);
	atomic_set(&chip->count, 0);

	dprintk(1,
		"Start audio DMA, %d B/line, %d lines/FIFO, %d periods, %d byte buffer\n",
		buf->bpl, cx_read(audio_ch->cmds_start + 8) >> 1,
		chip->num_periods, buf->bpl * chip->num_periods);

	/* Enables corresponding bits at AUD_INT_STAT */
	cx_write(MO_AUD_INTMSK, AUD_INT_OPC_ERR | AUD_INT_DN_SYNC |
				AUD_INT_DN_RISCI2 | AUD_INT_DN_RISCI1);

	/* Clean any pending interrupt bits already set */
	cx_write(MO_AUD_INTSTAT, ~0);

	/* enable audio irqs */
	cx_set(MO_PCI_INTMSK, chip->core->pci_irqmask | PCI_INT_AUDINT);

	/* start dma */

	/* Enables Risc Processor */
	cx_set(MO_DEV_CNTRL2, (1 << 5));
	/* audio downstream FIFO and RISC enable */
	cx_set(MO_AUD_DMACNTRL, 0x11);

	if (debug)
		cx88_sram_channel_dump(chip->core, audio_ch);

	return 0;
}