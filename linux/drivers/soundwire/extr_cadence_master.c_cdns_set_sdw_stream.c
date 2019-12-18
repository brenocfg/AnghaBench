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
struct snd_soc_dai {struct sdw_cdns_dma_data* capture_dma_data; struct sdw_cdns_dma_data* playback_dma_data; } ;
struct sdw_cdns_dma_data {void* stream; int /*<<< orphan*/  link_id; int /*<<< orphan*/ * bus; int /*<<< orphan*/  stream_type; } ;
struct sdw_cdns {int /*<<< orphan*/  instance; int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SDW_STREAM_PCM ; 
 int /*<<< orphan*/  SDW_STREAM_PDM ; 
 int SNDRV_PCM_STREAM_PLAYBACK ; 
 struct sdw_cdns_dma_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct sdw_cdns* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

int cdns_set_sdw_stream(struct snd_soc_dai *dai,
			void *stream, bool pcm, int direction)
{
	struct sdw_cdns *cdns = snd_soc_dai_get_drvdata(dai);
	struct sdw_cdns_dma_data *dma;

	dma = kzalloc(sizeof(*dma), GFP_KERNEL);
	if (!dma)
		return -ENOMEM;

	if (pcm)
		dma->stream_type = SDW_STREAM_PCM;
	else
		dma->stream_type = SDW_STREAM_PDM;

	dma->bus = &cdns->bus;
	dma->link_id = cdns->instance;

	dma->stream = stream;

	if (direction == SNDRV_PCM_STREAM_PLAYBACK)
		dai->playback_dma_data = dma;
	else
		dai->capture_dma_data = dma;

	return 0;
}