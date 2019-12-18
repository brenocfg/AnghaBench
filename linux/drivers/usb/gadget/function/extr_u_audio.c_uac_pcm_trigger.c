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
struct uac_rtd_params {int max_psize; int /*<<< orphan*/  rbuf; struct snd_pcm_substream* ss; int /*<<< orphan*/  lock; scalar_t__ hw_ptr; } ;
struct uac_params {int req_number; } ;
struct snd_uac_chip {struct uac_rtd_params c_prm; struct uac_rtd_params p_prm; struct g_audio* audio_dev; } ;
struct snd_pcm_substream {scalar_t__ stream; } ;
struct g_audio {struct uac_params params; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct snd_uac_chip* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int uac_pcm_trigger(struct snd_pcm_substream *substream, int cmd)
{
	struct snd_uac_chip *uac = snd_pcm_substream_chip(substream);
	struct uac_rtd_params *prm;
	struct g_audio *audio_dev;
	struct uac_params *params;
	unsigned long flags;
	int err = 0;

	audio_dev = uac->audio_dev;
	params = &audio_dev->params;

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		prm = &uac->p_prm;
	else
		prm = &uac->c_prm;

	spin_lock_irqsave(&prm->lock, flags);

	/* Reset */
	prm->hw_ptr = 0;

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_RESUME:
		prm->ss = substream;
		break;
	case SNDRV_PCM_TRIGGER_STOP:
	case SNDRV_PCM_TRIGGER_SUSPEND:
		prm->ss = NULL;
		break;
	default:
		err = -EINVAL;
	}

	spin_unlock_irqrestore(&prm->lock, flags);

	/* Clear buffer after Play stops */
	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK && !prm->ss)
		memset(prm->rbuf, 0, prm->max_psize * params->req_number);

	return err;
}