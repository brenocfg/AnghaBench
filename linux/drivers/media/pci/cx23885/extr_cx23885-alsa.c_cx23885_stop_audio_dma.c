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
struct cx23885_dev {int /*<<< orphan*/ * sram_channels; } ;
struct cx23885_audio_dev {struct cx23885_dev* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO_INT_INT_MSK ; 
 size_t AUDIO_SRAM_CHANNEL ; 
 int /*<<< orphan*/  AUD_INT_DMA_CTL ; 
 int AUD_INT_DN_RISCI1 ; 
 int AUD_INT_DN_SYNC ; 
 int AUD_INT_OPC_ERR ; 
 int /*<<< orphan*/  PCI_INT_MSK ; 
 int PCI_MSK_AUD_INT ; 
 scalar_t__ audio_debug ; 
 int /*<<< orphan*/  cx23885_sram_channel_dump (struct cx23885_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cx_clear (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dprintk (int,char*) ; 

__attribute__((used)) static int cx23885_stop_audio_dma(struct cx23885_audio_dev *chip)
{
	struct cx23885_dev *dev = chip->dev;
	dprintk(1, "Stopping audio DMA\n");

	/* stop dma */
	cx_clear(AUD_INT_DMA_CTL, 0x11);

	/* disable irqs */
	cx_clear(PCI_INT_MSK, PCI_MSK_AUD_INT);
	cx_clear(AUDIO_INT_INT_MSK, AUD_INT_OPC_ERR | AUD_INT_DN_SYNC |
				    AUD_INT_DN_RISCI1);

	if (audio_debug)
		cx23885_sram_channel_dump(chip->dev,
			&dev->sram_channels[AUDIO_SRAM_CHANNEL]);

	return 0;
}