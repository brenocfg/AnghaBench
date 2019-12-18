#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_substream {TYPE_1__* runtime; struct snd_dw_hdmi* private_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  hdmi; } ;
struct snd_dw_hdmi {int /*<<< orphan*/  lock; TYPE_2__ data; struct snd_pcm_substream* substream; int /*<<< orphan*/  buf_offset; } ;
struct TYPE_3__ {int /*<<< orphan*/  period_size; int /*<<< orphan*/  delay; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SNDRV_PCM_TRIGGER_START 129 
#define  SNDRV_PCM_TRIGGER_STOP 128 
 int /*<<< orphan*/  dw_hdmi_audio_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dw_hdmi_audio_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dw_hdmi_start_dma (struct snd_dw_hdmi*) ; 
 int /*<<< orphan*/  dw_hdmi_stop_dma (struct snd_dw_hdmi*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int dw_hdmi_trigger(struct snd_pcm_substream *substream, int cmd)
{
	struct snd_dw_hdmi *dw = substream->private_data;
	unsigned long flags;
	int ret = 0;

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
		spin_lock_irqsave(&dw->lock, flags);
		dw->buf_offset = 0;
		dw->substream = substream;
		dw_hdmi_start_dma(dw);
		dw_hdmi_audio_enable(dw->data.hdmi);
		spin_unlock_irqrestore(&dw->lock, flags);
		substream->runtime->delay = substream->runtime->period_size;
		break;

	case SNDRV_PCM_TRIGGER_STOP:
		spin_lock_irqsave(&dw->lock, flags);
		dw->substream = NULL;
		dw_hdmi_stop_dma(dw);
		dw_hdmi_audio_disable(dw->data.hdmi);
		spin_unlock_irqrestore(&dw->lock, flags);
		break;

	default:
		ret = -EINVAL;
		break;
	}

	return ret;
}