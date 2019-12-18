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
struct snd_cobalt_card {int alsa_pb_channel; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
#define  SNDRV_PCM_TRIGGER_START 129 
#define  SNDRV_PCM_TRIGGER_STOP 128 
 struct snd_cobalt_card* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_cobalt_pcm_pb_trigger(struct snd_pcm_substream *substream,
				     int cmd)
{
	struct snd_cobalt_card *cobsc = snd_pcm_substream_chip(substream);

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
		if (cobsc->alsa_pb_channel)
			return -EBUSY;
		cobsc->alsa_pb_channel = true;
		return 0;
	case SNDRV_PCM_TRIGGER_STOP:
		cobsc->alsa_pb_channel = false;
		return 0;
	default:
		return -EINVAL;
	}
}