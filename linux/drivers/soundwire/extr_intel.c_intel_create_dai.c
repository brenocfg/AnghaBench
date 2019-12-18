#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int channels_min; int channels_max; void* formats; void* rates; void* stream_name; } ;
struct TYPE_3__ {int channels_min; int channels_max; void* stream_name; void* formats; void* rates; } ;
struct snd_soc_dai_driver {int /*<<< orphan*/ * ops; scalar_t__ id; TYPE_2__ capture; TYPE_1__ playback; void* name; } ;
struct sdw_cdns {int /*<<< orphan*/  instance; } ;
typedef  enum intel_pdi_type { ____Placeholder_intel_pdi_type } intel_pdi_type ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int INTEL_PDI_BD ; 
 int INTEL_PDI_IN ; 
 int INTEL_PDI_OUT ; 
 scalar_t__ SDW_DAI_ID_RANGE_START ; 
 void* SNDRV_PCM_FMTBIT_S16_LE ; 
 void* SNDRV_PCM_RATE_48000 ; 
 int /*<<< orphan*/  intel_pcm_dai_ops ; 
 int /*<<< orphan*/  intel_pdm_dai_ops ; 
 void* kasprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree (void*) ; 

__attribute__((used)) static int intel_create_dai(struct sdw_cdns *cdns,
			    struct snd_soc_dai_driver *dais,
			    enum intel_pdi_type type,
			    u32 num, u32 off, u32 max_ch, bool pcm)
{
	int i;

	if (num == 0)
		return 0;

	 /* TODO: Read supported rates/formats from hardware */
	for (i = off; i < (off + num); i++) {
		dais[i].name = kasprintf(GFP_KERNEL, "SDW%d Pin%d",
					 cdns->instance, i);
		if (!dais[i].name)
			return -ENOMEM;

		if (type == INTEL_PDI_BD || type == INTEL_PDI_OUT) {
			dais[i].playback.stream_name =
				kasprintf(GFP_KERNEL, "SDW%d Tx%d",
					  cdns->instance, i);
			if (!dais[i].playback.stream_name) {
				kfree(dais[i].name);
				return -ENOMEM;
			}

			dais[i].playback.channels_min = 1;
			dais[i].playback.channels_max = max_ch;
			dais[i].playback.rates = SNDRV_PCM_RATE_48000;
			dais[i].playback.formats = SNDRV_PCM_FMTBIT_S16_LE;
		}

		if (type == INTEL_PDI_BD || type == INTEL_PDI_IN) {
			dais[i].capture.stream_name =
				kasprintf(GFP_KERNEL, "SDW%d Rx%d",
					  cdns->instance, i);
			if (!dais[i].capture.stream_name) {
				kfree(dais[i].name);
				kfree(dais[i].playback.stream_name);
				return -ENOMEM;
			}

			dais[i].capture.channels_min = 1;
			dais[i].capture.channels_max = max_ch;
			dais[i].capture.rates = SNDRV_PCM_RATE_48000;
			dais[i].capture.formats = SNDRV_PCM_FMTBIT_S16_LE;
		}

		dais[i].id = SDW_DAI_ID_RANGE_START + i;

		if (pcm)
			dais[i].ops = &intel_pcm_dai_ops;
		else
			dais[i].ops = &intel_pdm_dai_ops;
	}

	return 0;
}