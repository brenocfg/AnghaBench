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
struct cx25821_dev {int /*<<< orphan*/  name; } ;
struct cx25821_audio_dev {int /*<<< orphan*/  substream; int /*<<< orphan*/  count; struct cx25821_dev* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 size_t AUDIO_SRAM_CHANNEL ; 
 int /*<<< orphan*/  AUD_A_GPCNT ; 
 int /*<<< orphan*/  AUD_A_GPCNT_CTL ; 
 int /*<<< orphan*/  AUD_A_INT_STAT ; 
 int /*<<< orphan*/  AUD_INT_DMA_CTL ; 
 int AUD_INT_DN_RISCI1 ; 
 int AUD_INT_DN_SYNC ; 
 int AUD_INT_OPC_ERR ; 
 int FLD_AUD_DST_A_FIFO_EN ; 
 int FLD_AUD_DST_A_RISC_EN ; 
 int GP_COUNT_CONTROL_RESET ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx25821_aud_irqs ; 
 int /*<<< orphan*/  cx25821_print_irqbits (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cx25821_sram_channel_dump_audio (struct cx25821_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cx25821_sram_channels ; 
 int /*<<< orphan*/  cx_clear (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cx_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx_write (int /*<<< orphan*/ ,int) ; 
 int debug ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_period_elapsed (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cx25821_aud_irq(struct cx25821_audio_dev *chip, u32 status,
			    u32 mask)
{
	struct cx25821_dev *dev = chip->dev;

	if (0 == (status & mask))
		return;

	cx_write(AUD_A_INT_STAT, status);
	if (debug > 1 || (status & mask & ~0xff))
		cx25821_print_irqbits(dev->name, "irq aud", cx25821_aud_irqs,
				ARRAY_SIZE(cx25821_aud_irqs), status, mask);

	/* risc op code error */
	if (status & AUD_INT_OPC_ERR) {
		pr_warn("WARNING %s/1: Audio risc op code error\n", dev->name);

		cx_clear(AUD_INT_DMA_CTL,
			 FLD_AUD_DST_A_RISC_EN | FLD_AUD_DST_A_FIFO_EN);
		cx25821_sram_channel_dump_audio(dev,
				&cx25821_sram_channels[AUDIO_SRAM_CHANNEL]);
	}
	if (status & AUD_INT_DN_SYNC) {
		pr_warn("WARNING %s: Downstream sync error!\n", dev->name);
		cx_write(AUD_A_GPCNT_CTL, GP_COUNT_CONTROL_RESET);
		return;
	}

	/* risc1 downstream */
	if (status & AUD_INT_DN_RISCI1) {
		atomic_set(&chip->count, cx_read(AUD_A_GPCNT));
		snd_pcm_period_elapsed(chip->substream);
	}
}