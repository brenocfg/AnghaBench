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
struct solo_snd_pcm {int on; int /*<<< orphan*/  lock; struct solo_dev* solo_dev; } ;
struct solo_dev {int /*<<< orphan*/  snd_users; } ;
struct snd_pcm_substream {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SNDRV_PCM_TRIGGER_START 129 
#define  SNDRV_PCM_TRIGGER_STOP 128 
 int /*<<< orphan*/  SOLO_IRQ_G723 ; 
 int /*<<< orphan*/  atomic_dec_return (int /*<<< orphan*/ *) ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 struct solo_snd_pcm* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  solo_irq_off (struct solo_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  solo_irq_on (struct solo_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_solo_pcm_trigger(struct snd_pcm_substream *ss, int cmd)
{
	struct solo_snd_pcm *solo_pcm = snd_pcm_substream_chip(ss);
	struct solo_dev *solo_dev = solo_pcm->solo_dev;
	int ret = 0;

	spin_lock(&solo_pcm->lock);

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
		if (solo_pcm->on == 0) {
			/* If this is the first user, switch on interrupts */
			if (atomic_inc_return(&solo_dev->snd_users) == 1)
				solo_irq_on(solo_dev, SOLO_IRQ_G723);
			solo_pcm->on = 1;
		}
		break;
	case SNDRV_PCM_TRIGGER_STOP:
		if (solo_pcm->on) {
			/* If this was our last user, switch them off */
			if (atomic_dec_return(&solo_dev->snd_users) == 0)
				solo_irq_off(solo_dev, SOLO_IRQ_G723);
			solo_pcm->on = 0;
		}
		break;
	default:
		ret = -EINVAL;
	}

	spin_unlock(&solo_pcm->lock);

	return ret;
}