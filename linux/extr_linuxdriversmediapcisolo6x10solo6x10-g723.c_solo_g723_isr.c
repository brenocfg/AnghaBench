#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct solo_snd_pcm {int /*<<< orphan*/  on; TYPE_1__* snd_pcm; } ;
struct solo_dev {int /*<<< orphan*/  on; TYPE_1__* snd_pcm; } ;
struct snd_pcm_substream {struct snd_pcm_substream* next; } ;
struct snd_pcm_str {struct snd_pcm_substream* substream; } ;
struct TYPE_2__ {struct snd_pcm_str* streams; } ;

/* Variables and functions */
 size_t SNDRV_PCM_STREAM_CAPTURE ; 
 int /*<<< orphan*/  snd_pcm_period_elapsed (struct snd_pcm_substream*) ; 
 struct solo_snd_pcm* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

void solo_g723_isr(struct solo_dev *solo_dev)
{
	struct snd_pcm_str *pstr =
		&solo_dev->snd_pcm->streams[SNDRV_PCM_STREAM_CAPTURE];
	struct snd_pcm_substream *ss;
	struct solo_snd_pcm *solo_pcm;

	for (ss = pstr->substream; ss != NULL; ss = ss->next) {
		if (snd_pcm_substream_chip(ss) == NULL)
			continue;

		/* This means open() hasn't been called on this one */
		if (snd_pcm_substream_chip(ss) == solo_dev)
			continue;

		/* Haven't triggered a start yet */
		solo_pcm = snd_pcm_substream_chip(ss);
		if (!solo_pcm->on)
			continue;

		snd_pcm_period_elapsed(ss);
	}
}