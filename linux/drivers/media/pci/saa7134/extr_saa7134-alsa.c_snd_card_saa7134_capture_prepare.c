#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int channels; int /*<<< orphan*/  rate; int /*<<< orphan*/  format; TYPE_7__* private_data; } ;
struct TYPE_12__ {int dma; } ;
struct TYPE_13__ {size_t input; int blksize; int /*<<< orphan*/  rate; TYPE_4__ pt; } ;
struct saa7134_dev {TYPE_5__ dmasound; TYPE_3__* pci; } ;
struct TYPE_14__ {int /*<<< orphan*/ * capture_ctl; struct saa7134_dev* dev; } ;
typedef  TYPE_6__ snd_card_saa7134_t ;
struct TYPE_15__ {TYPE_2__* dev; } ;
typedef  TYPE_7__ snd_card_saa7134_pcm_t ;
struct TYPE_11__ {int device; } ;
struct TYPE_9__ {struct snd_pcm_substream* substream; } ;
struct TYPE_10__ {TYPE_1__ dmasound; } ;

/* Variables and functions */
 size_t MIXER_ADDR_TVTUNER ; 
#define  PCI_DEVICE_ID_PHILIPS_SAA7133 130 
#define  PCI_DEVICE_ID_PHILIPS_SAA7134 129 
#define  PCI_DEVICE_ID_PHILIPS_SAA7135 128 
 int /*<<< orphan*/  SAA7133_AUDIO_CHANNEL ; 
 int /*<<< orphan*/  SAA7133_NUM_SAMPLES ; 
 int /*<<< orphan*/  SAA7134_AUDIO_FORMAT_CTRL ; 
 int /*<<< orphan*/  SAA7134_NUM_SAMPLES0 ; 
 int /*<<< orphan*/  SAA7134_NUM_SAMPLES1 ; 
 int /*<<< orphan*/  SAA7134_NUM_SAMPLES2 ; 
 int /*<<< orphan*/  SAA7134_RS_BA1 (int) ; 
 int /*<<< orphan*/  SAA7134_RS_BA2 (int) ; 
 int /*<<< orphan*/  SAA7134_RS_CONTROL (int) ; 
 int SAA7134_RS_CONTROL_BSWAP ; 
 int SAA7134_RS_CONTROL_BURST_16 ; 
 int SAA7134_RS_CONTROL_ME ; 
 int /*<<< orphan*/  SAA7134_RS_PITCH (int) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int,int,char) ; 
 int /*<<< orphan*/  saa_writeb (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  saa_writel (int /*<<< orphan*/ ,int) ; 
 scalar_t__ snd_pcm_format_big_endian (int /*<<< orphan*/ ) ; 
 scalar_t__ snd_pcm_format_signed (int /*<<< orphan*/ ) ; 
 int snd_pcm_format_width (int /*<<< orphan*/ ) ; 
 TYPE_6__* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_saa7134_capsrc_set (int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int snd_card_saa7134_capture_prepare(struct snd_pcm_substream * substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	int bswap, sign;
	u32 fmt, control;
	snd_card_saa7134_t *saa7134 = snd_pcm_substream_chip(substream);
	struct saa7134_dev *dev;
	snd_card_saa7134_pcm_t *pcm = runtime->private_data;

	pcm->dev->dmasound.substream = substream;

	dev = saa7134->dev;

	if (snd_pcm_format_width(runtime->format) == 8)
		fmt = 0x00;
	else
		fmt = 0x01;

	if (snd_pcm_format_signed(runtime->format))
		sign = 1;
	else
		sign = 0;

	if (snd_pcm_format_big_endian(runtime->format))
		bswap = 1;
	else
		bswap = 0;

	switch (dev->pci->device) {
	  case PCI_DEVICE_ID_PHILIPS_SAA7134:
		if (1 == runtime->channels)
			fmt |= (1 << 3);
		if (2 == runtime->channels)
			fmt |= (3 << 3);
		if (sign)
			fmt |= 0x04;

		fmt |= (MIXER_ADDR_TVTUNER == dev->dmasound.input) ? 0xc0 : 0x80;
		saa_writeb(SAA7134_NUM_SAMPLES0, ((dev->dmasound.blksize - 1) & 0x0000ff));
		saa_writeb(SAA7134_NUM_SAMPLES1, ((dev->dmasound.blksize - 1) & 0x00ff00) >>  8);
		saa_writeb(SAA7134_NUM_SAMPLES2, ((dev->dmasound.blksize - 1) & 0xff0000) >> 16);
		saa_writeb(SAA7134_AUDIO_FORMAT_CTRL, fmt);

		break;
	  case PCI_DEVICE_ID_PHILIPS_SAA7133:
	  case PCI_DEVICE_ID_PHILIPS_SAA7135:
		if (1 == runtime->channels)
			fmt |= (1 << 4);
		if (2 == runtime->channels)
			fmt |= (2 << 4);
		if (!sign)
			fmt |= 0x04;
		saa_writel(SAA7133_NUM_SAMPLES, dev->dmasound.blksize -1);
		saa_writel(SAA7133_AUDIO_CHANNEL, 0x543210 | (fmt << 24));
		break;
	}

	pr_debug("rec_start: afmt=%d ch=%d  =>  fmt=0x%x swap=%c\n",
		runtime->format, runtime->channels, fmt,
		bswap ? 'b' : '-');
	/* dma: setup channel 6 (= AUDIO) */
	control = SAA7134_RS_CONTROL_BURST_16 |
		SAA7134_RS_CONTROL_ME |
		(dev->dmasound.pt.dma >> 12);
	if (bswap)
		control |= SAA7134_RS_CONTROL_BSWAP;

	saa_writel(SAA7134_RS_BA1(6),0);
	saa_writel(SAA7134_RS_BA2(6),dev->dmasound.blksize);
	saa_writel(SAA7134_RS_PITCH(6),0);
	saa_writel(SAA7134_RS_CONTROL(6),control);

	dev->dmasound.rate = runtime->rate;

	/* Setup and update the card/ALSA controls */
	snd_saa7134_capsrc_set(saa7134->capture_ctl[dev->dmasound.input], 1, 1,
			       true);

	return 0;

}