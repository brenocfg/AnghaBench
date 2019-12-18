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
struct snd_pcm_indirect {int dummy; } ;
struct bcm2835_alsa_stream {struct snd_pcm_indirect pcm_indirect; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_bcm2835_pcm_transfer ; 
 int snd_pcm_indirect_playback_transfer (struct snd_pcm_substream*,struct snd_pcm_indirect*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_bcm2835_pcm_ack(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct bcm2835_alsa_stream *alsa_stream = runtime->private_data;
	struct snd_pcm_indirect *pcm_indirect = &alsa_stream->pcm_indirect;

	return snd_pcm_indirect_playback_transfer(substream, pcm_indirect,
						  snd_bcm2835_pcm_transfer);
}