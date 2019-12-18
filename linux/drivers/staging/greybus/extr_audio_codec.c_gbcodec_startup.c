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
struct snd_soc_dai {int /*<<< orphan*/  dev; int /*<<< orphan*/  id; } ;
struct snd_pcm_substream {int /*<<< orphan*/  stream; } ;
struct gbaudio_stream_params {int /*<<< orphan*/  state; } ;
struct gbaudio_codec_info {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; int /*<<< orphan*/  module_list; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  GBAUDIO_CODEC_STARTUP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct gbaudio_codec_info* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct gbaudio_stream_params* find_dai_stream_params (struct gbaudio_codec_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_stay_awake (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gbcodec_startup(struct snd_pcm_substream *substream,
			   struct snd_soc_dai *dai)
{
	struct gbaudio_codec_info *codec = dev_get_drvdata(dai->dev);
	struct gbaudio_stream_params *params;

	mutex_lock(&codec->lock);

	if (list_empty(&codec->module_list)) {
		dev_err(codec->dev, "No codec module available\n");
		mutex_unlock(&codec->lock);
		return -ENODEV;
	}

	params = find_dai_stream_params(codec, dai->id, substream->stream);
	if (!params) {
		dev_err(codec->dev, "Failed to fetch dai_stream pointer\n");
		mutex_unlock(&codec->lock);
		return -EINVAL;
	}
	params->state = GBAUDIO_CODEC_STARTUP;
	mutex_unlock(&codec->lock);
	/* to prevent suspend in case of active audio */
	pm_stay_awake(dai->dev);

	return 0;
}