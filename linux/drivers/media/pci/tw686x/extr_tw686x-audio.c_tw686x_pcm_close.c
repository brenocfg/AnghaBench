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
struct tw686x_dev {struct tw686x_audio_channel* audio_channels; } ;
struct tw686x_audio_channel {int /*<<< orphan*/ * ss; } ;
struct snd_pcm_substream {size_t number; } ;

/* Variables and functions */
 struct tw686x_dev* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int tw686x_pcm_close(struct snd_pcm_substream *ss)
{
	struct tw686x_dev *dev = snd_pcm_substream_chip(ss);
	struct tw686x_audio_channel *ac = &dev->audio_channels[ss->number];

	ac->ss = NULL;
	return 0;
}