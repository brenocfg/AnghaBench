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
struct snd_tm6000_card {int dummy; } ;
struct snd_pcm_substream {TYPE_1__* runtime; } ;
struct TYPE_2__ {int dma_bytes; scalar_t__ dma_area; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  dprintk (int,char*) ; 
 int /*<<< orphan*/  dsp_buffer_free (struct snd_pcm_substream*) ; 
 struct snd_tm6000_card* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 scalar_t__ vmalloc (int) ; 

__attribute__((used)) static int dsp_buffer_alloc(struct snd_pcm_substream *substream, int size)
{
	struct snd_tm6000_card *chip = snd_pcm_substream_chip(substream);

	dprintk(2, "Allocating buffer\n");

	if (substream->runtime->dma_area) {
		if (substream->runtime->dma_bytes > size)
			return 0;

		dsp_buffer_free(substream);
	}

	substream->runtime->dma_area = vmalloc(size);
	if (!substream->runtime->dma_area)
		return -ENOMEM;

	substream->runtime->dma_bytes = size;

	return 0;
}