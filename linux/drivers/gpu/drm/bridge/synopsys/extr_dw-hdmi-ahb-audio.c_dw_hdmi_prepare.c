#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_7__ {int /*<<< orphan*/  addr; int /*<<< orphan*/  area; } ;
struct snd_pcm_substream {TYPE_3__ dma_buffer; struct snd_dw_hdmi* private_data; struct snd_pcm_runtime* runtime; } ;
struct TYPE_5__ {int fifo_size; } ;
struct snd_pcm_runtime {int channels; int format; int /*<<< orphan*/  dma_area; TYPE_1__ hw; int /*<<< orphan*/  rate; } ;
struct TYPE_6__ {int /*<<< orphan*/  hdmi; scalar_t__ base; } ;
struct snd_dw_hdmi {int revision; int channels; int /*<<< orphan*/  buf_size; int /*<<< orphan*/  buf_period; int /*<<< orphan*/  buf_addr; int /*<<< orphan*/  buf_dst; int /*<<< orphan*/  buf_src; scalar_t__ iec_offset; int /*<<< orphan*/  reformat; TYPE_2__ data; } ;
struct TYPE_8__ {int conf1; int ca; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ HDMI_AHB_DMA_CONF0 ; 
 int HDMI_AHB_DMA_CONF0_BURST_MODE ; 
 int HDMI_AHB_DMA_CONF0_EN_HLOCK ; 
 int HDMI_AHB_DMA_CONF0_INCR4 ; 
 int HDMI_AHB_DMA_CONF0_INCR8 ; 
 scalar_t__ HDMI_AHB_DMA_CONF1 ; 
 scalar_t__ HDMI_AHB_DMA_THRSLD ; 
#define  SNDRV_PCM_FORMAT_IEC958_SUBFRAME_LE 129 
#define  SNDRV_PCM_FORMAT_S24_LE 128 
 TYPE_4__* default_hdmi_channel_config ; 
 int /*<<< orphan*/  dw_hdmi_create_cs (struct snd_dw_hdmi*,struct snd_pcm_runtime*) ; 
 int /*<<< orphan*/  dw_hdmi_reformat_iec958 ; 
 int /*<<< orphan*/  dw_hdmi_reformat_s24 ; 
 int /*<<< orphan*/  dw_hdmi_set_channel_allocation (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dw_hdmi_set_channel_count (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dw_hdmi_set_sample_rate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_lib_buffer_bytes (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_pcm_lib_period_bytes (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  writeb_relaxed (int,scalar_t__) ; 

__attribute__((used)) static int dw_hdmi_prepare(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct snd_dw_hdmi *dw = substream->private_data;
	u8 threshold, conf0, conf1, ca;

	/* Setup as per 3.0.5 FSL 4.1.0 BSP */
	switch (dw->revision) {
	case 0x0a:
		conf0 = HDMI_AHB_DMA_CONF0_BURST_MODE |
			HDMI_AHB_DMA_CONF0_INCR4;
		if (runtime->channels == 2)
			threshold = 126;
		else
			threshold = 124;
		break;
	case 0x1a:
		conf0 = HDMI_AHB_DMA_CONF0_BURST_MODE |
			HDMI_AHB_DMA_CONF0_INCR8;
		threshold = 128;
		break;
	default:
		/* NOTREACHED */
		return -EINVAL;
	}

	dw_hdmi_set_sample_rate(dw->data.hdmi, runtime->rate);

	/* Minimum number of bytes in the fifo. */
	runtime->hw.fifo_size = threshold * 32;

	conf0 |= HDMI_AHB_DMA_CONF0_EN_HLOCK;
	conf1 = default_hdmi_channel_config[runtime->channels - 2].conf1;
	ca = default_hdmi_channel_config[runtime->channels - 2].ca;

	writeb_relaxed(threshold, dw->data.base + HDMI_AHB_DMA_THRSLD);
	writeb_relaxed(conf0, dw->data.base + HDMI_AHB_DMA_CONF0);
	writeb_relaxed(conf1, dw->data.base + HDMI_AHB_DMA_CONF1);

	dw_hdmi_set_channel_count(dw->data.hdmi, runtime->channels);
	dw_hdmi_set_channel_allocation(dw->data.hdmi, ca);

	switch (runtime->format) {
	case SNDRV_PCM_FORMAT_IEC958_SUBFRAME_LE:
		dw->reformat = dw_hdmi_reformat_iec958;
		break;
	case SNDRV_PCM_FORMAT_S24_LE:
		dw_hdmi_create_cs(dw, runtime);
		dw->reformat = dw_hdmi_reformat_s24;
		break;
	}
	dw->iec_offset = 0;
	dw->channels = runtime->channels;
	dw->buf_src  = runtime->dma_area;
	dw->buf_dst  = substream->dma_buffer.area;
	dw->buf_addr = substream->dma_buffer.addr;
	dw->buf_period = snd_pcm_lib_period_bytes(substream);
	dw->buf_size = snd_pcm_lib_buffer_bytes(substream);

	return 0;
}