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
struct snd_pcm_substream {int dummy; } ;
struct cx25821_audio_dev {int /*<<< orphan*/  reg_lock; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SNDRV_PCM_TRIGGER_START 129 
#define  SNDRV_PCM_TRIGGER_STOP 128 
 int _cx25821_start_audio_dma (struct cx25821_audio_dev*) ; 
 int _cx25821_stop_audio_dma (struct cx25821_audio_dev*) ; 
 struct cx25821_audio_dev* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_cx25821_card_trigger(struct snd_pcm_substream *substream,
				    int cmd)
{
	struct cx25821_audio_dev *chip = snd_pcm_substream_chip(substream);
	int err = 0;

	/* Local interrupts are already disabled by ALSA */
	spin_lock(&chip->reg_lock);

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
		err = _cx25821_start_audio_dma(chip);
		break;
	case SNDRV_PCM_TRIGGER_STOP:
		err = _cx25821_stop_audio_dma(chip);
		break;
	default:
		err = -EINVAL;
		break;
	}

	spin_unlock(&chip->reg_lock);

	return err;
}