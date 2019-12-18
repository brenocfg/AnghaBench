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
struct snd_soc_dai {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {int dummy; } ;
struct sdw_cdns_dma_data {int /*<<< orphan*/  port; TYPE_1__* stream; } ;
struct sdw_cdns {int /*<<< orphan*/  bus; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  intel_port_cleanup (struct sdw_cdns_dma_data*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int sdw_stream_remove_master (int /*<<< orphan*/ *,TYPE_1__*) ; 
 struct sdw_cdns_dma_data* snd_soc_dai_get_dma_data (struct snd_soc_dai*,struct snd_pcm_substream*) ; 
 struct sdw_cdns* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int
intel_hw_free(struct snd_pcm_substream *substream, struct snd_soc_dai *dai)
{
	struct sdw_cdns *cdns = snd_soc_dai_get_drvdata(dai);
	struct sdw_cdns_dma_data *dma;
	int ret;

	dma = snd_soc_dai_get_dma_data(dai, substream);
	if (!dma)
		return -EIO;

	ret = sdw_stream_remove_master(&cdns->bus, dma->stream);
	if (ret < 0)
		dev_err(dai->dev, "remove master from stream %s failed: %d\n",
			dma->stream->name, ret);

	intel_port_cleanup(dma);
	kfree(dma->port);
	return ret;
}