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
struct go7007_snd {int capturing; int /*<<< orphan*/  avail; int /*<<< orphan*/  w_idx; int /*<<< orphan*/  hw_ptr; } ;
struct go7007 {struct go7007_snd* snd_context; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SNDRV_PCM_TRIGGER_START 129 
#define  SNDRV_PCM_TRIGGER_STOP 128 
 struct go7007* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int go7007_snd_pcm_trigger(struct snd_pcm_substream *substream, int cmd)
{
	struct go7007 *go = snd_pcm_substream_chip(substream);
	struct go7007_snd *gosnd = go->snd_context;

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
		/* Just set a flag to indicate we should signal ALSA when
		 * sound comes in */
		gosnd->capturing = 1;
		return 0;
	case SNDRV_PCM_TRIGGER_STOP:
		gosnd->hw_ptr = gosnd->w_idx = gosnd->avail = 0;
		gosnd->capturing = 0;
		return 0;
	default:
		return -EINVAL;
	}
}