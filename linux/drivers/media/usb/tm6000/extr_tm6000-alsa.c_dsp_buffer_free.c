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
struct TYPE_2__ {scalar_t__ dma_bytes; int /*<<< orphan*/ * dma_area; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (int,char*) ; 
 struct snd_tm6000_card* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dsp_buffer_free(struct snd_pcm_substream *substream)
{
	struct snd_tm6000_card *chip = snd_pcm_substream_chip(substream);

	dprintk(2, "Freeing buffer\n");

	vfree(substream->runtime->dma_area);
	substream->runtime->dma_area = NULL;
	substream->runtime->dma_bytes = 0;
}