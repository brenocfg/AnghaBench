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
struct tw686x_dev {int audio_enabled; int /*<<< orphan*/  lock; int /*<<< orphan*/  dma_delay_timer; struct tw686x_audio_channel* audio_channels; } ;
struct tw686x_audio_channel {int /*<<< orphan*/  lock; int /*<<< orphan*/ ** curr_bufs; scalar_t__ ch; } ;
struct snd_pcm_substream {size_t number; } ;

/* Variables and functions */
 scalar_t__ AUDIO_CHANNEL_OFFSET ; 
 int EINVAL ; 
 int EIO ; 
#define  SNDRV_PCM_TRIGGER_START 129 
#define  SNDRV_PCM_TRIGGER_STOP 128 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 struct tw686x_dev* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tw686x_disable_channel (struct tw686x_dev*,scalar_t__) ; 
 int /*<<< orphan*/  tw686x_enable_channel (struct tw686x_dev*,scalar_t__) ; 

__attribute__((used)) static int tw686x_pcm_trigger(struct snd_pcm_substream *ss, int cmd)
{
	struct tw686x_dev *dev = snd_pcm_substream_chip(ss);
	struct tw686x_audio_channel *ac = &dev->audio_channels[ss->number];
	unsigned long flags;
	int err = 0;

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
		if (ac->curr_bufs[0] && ac->curr_bufs[1]) {
			spin_lock_irqsave(&dev->lock, flags);
			dev->audio_enabled = 1;
			tw686x_enable_channel(dev,
				AUDIO_CHANNEL_OFFSET + ac->ch);
			spin_unlock_irqrestore(&dev->lock, flags);

			mod_timer(&dev->dma_delay_timer,
				  jiffies + msecs_to_jiffies(100));
		} else {
			err = -EIO;
		}
		break;
	case SNDRV_PCM_TRIGGER_STOP:
		spin_lock_irqsave(&dev->lock, flags);
		dev->audio_enabled = 0;
		tw686x_disable_channel(dev, AUDIO_CHANNEL_OFFSET + ac->ch);
		spin_unlock_irqrestore(&dev->lock, flags);

		spin_lock_irqsave(&ac->lock, flags);
		ac->curr_bufs[0] = NULL;
		ac->curr_bufs[1] = NULL;
		spin_unlock_irqrestore(&ac->lock, flags);
		break;
	default:
		err = -EINVAL;
	}
	return err;
}