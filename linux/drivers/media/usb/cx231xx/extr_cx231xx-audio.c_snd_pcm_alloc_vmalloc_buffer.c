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
struct snd_pcm_runtime {size_t dma_bytes; scalar_t__ dma_area; } ;
struct cx231xx {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 struct cx231xx* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  vfree (scalar_t__) ; 
 scalar_t__ vmalloc (size_t) ; 

__attribute__((used)) static int snd_pcm_alloc_vmalloc_buffer(struct snd_pcm_substream *subs,
					size_t size)
{
	struct snd_pcm_runtime *runtime = subs->runtime;
	struct cx231xx *dev = snd_pcm_substream_chip(subs);

	dev_dbg(dev->dev, "Allocating vbuffer\n");
	if (runtime->dma_area) {
		if (runtime->dma_bytes > size)
			return 0;

		vfree(runtime->dma_area);
	}
	runtime->dma_area = vmalloc(size);
	if (!runtime->dma_area)
		return -ENOMEM;

	runtime->dma_bytes = size;

	return 0;
}