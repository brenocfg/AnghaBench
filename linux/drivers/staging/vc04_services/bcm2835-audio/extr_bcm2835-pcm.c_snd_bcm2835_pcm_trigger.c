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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {struct bcm2835_alsa_stream* private_data; } ;
struct bcm2835_alsa_stream {int draining; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SNDRV_PCM_TRIGGER_DRAIN 130 
#define  SNDRV_PCM_TRIGGER_START 129 
#define  SNDRV_PCM_TRIGGER_STOP 128 
 int bcm2835_audio_drain (struct bcm2835_alsa_stream*) ; 
 int bcm2835_audio_start (struct bcm2835_alsa_stream*) ; 
 int bcm2835_audio_stop (struct bcm2835_alsa_stream*) ; 

__attribute__((used)) static int snd_bcm2835_pcm_trigger(struct snd_pcm_substream *substream, int cmd)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct bcm2835_alsa_stream *alsa_stream = runtime->private_data;

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
		return bcm2835_audio_start(alsa_stream);
	case SNDRV_PCM_TRIGGER_DRAIN:
		alsa_stream->draining = true;
		return bcm2835_audio_drain(alsa_stream);
	case SNDRV_PCM_TRIGGER_STOP:
		return bcm2835_audio_stop(alsa_stream);
	default:
		return -EINVAL;
	}
}