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
struct snd_pcm_runtime {scalar_t__ dma_area; struct bcm2835_alsa_stream* private_data; } ;
struct snd_pcm_indirect {scalar_t__ sw_data; } ;
struct bcm2835_alsa_stream {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcm2835_audio_write (struct bcm2835_alsa_stream*,size_t,void*) ; 

__attribute__((used)) static void snd_bcm2835_pcm_transfer(struct snd_pcm_substream *substream,
	struct snd_pcm_indirect *rec, size_t bytes)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct bcm2835_alsa_stream *alsa_stream = runtime->private_data;
	void *src = (void *) (substream->runtime->dma_area + rec->sw_data);

	bcm2835_audio_write(alsa_stream, bytes, src);
}