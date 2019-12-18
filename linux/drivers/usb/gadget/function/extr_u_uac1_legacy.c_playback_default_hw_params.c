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
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct gaudio_snd_dev {int access; int format; int channels; int rate; int /*<<< orphan*/  card; struct snd_pcm_substream* substream; } ;
typedef  scalar_t__ snd_pcm_sframes_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  ERROR (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INFO (int /*<<< orphan*/ ,char*,int,int,int,int) ; 
 int SNDRV_PCM_ACCESS_RW_INTERLEAVED ; 
 int SNDRV_PCM_FORMAT_S16_LE ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_ACCESS ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_CHANNELS ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_FORMAT ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_RATE ; 
 int /*<<< orphan*/  SNDRV_PCM_IOCTL_DROP ; 
 int /*<<< orphan*/  SNDRV_PCM_IOCTL_HW_PARAMS ; 
 int /*<<< orphan*/  SNDRV_PCM_IOCTL_PREPARE ; 
 int /*<<< orphan*/  _snd_pcm_hw_param_set (struct snd_pcm_hw_params*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _snd_pcm_hw_params_any (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  kfree (struct snd_pcm_hw_params*) ; 
 struct snd_pcm_hw_params* kzalloc (int,int /*<<< orphan*/ ) ; 
 int params_access (struct snd_pcm_hw_params*) ; 
 int params_channels (struct snd_pcm_hw_params*) ; 
 int params_format (struct snd_pcm_hw_params*) ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 scalar_t__ snd_pcm_kernel_ioctl (struct snd_pcm_substream*,int /*<<< orphan*/ ,struct snd_pcm_hw_params*) ; 

__attribute__((used)) static int playback_default_hw_params(struct gaudio_snd_dev *snd)
{
	struct snd_pcm_substream *substream = snd->substream;
	struct snd_pcm_hw_params *params;
	snd_pcm_sframes_t result;

       /*
	* SNDRV_PCM_ACCESS_RW_INTERLEAVED,
	* SNDRV_PCM_FORMAT_S16_LE
	* CHANNELS: 2
	* RATE: 48000
	*/
	snd->access = SNDRV_PCM_ACCESS_RW_INTERLEAVED;
	snd->format = SNDRV_PCM_FORMAT_S16_LE;
	snd->channels = 2;
	snd->rate = 48000;

	params = kzalloc(sizeof(*params), GFP_KERNEL);
	if (!params)
		return -ENOMEM;

	_snd_pcm_hw_params_any(params);
	_snd_pcm_hw_param_set(params, SNDRV_PCM_HW_PARAM_ACCESS,
			snd->access, 0);
	_snd_pcm_hw_param_set(params, SNDRV_PCM_HW_PARAM_FORMAT,
			snd->format, 0);
	_snd_pcm_hw_param_set(params, SNDRV_PCM_HW_PARAM_CHANNELS,
			snd->channels, 0);
	_snd_pcm_hw_param_set(params, SNDRV_PCM_HW_PARAM_RATE,
			snd->rate, 0);

	snd_pcm_kernel_ioctl(substream, SNDRV_PCM_IOCTL_DROP, NULL);
	snd_pcm_kernel_ioctl(substream, SNDRV_PCM_IOCTL_HW_PARAMS, params);

	result = snd_pcm_kernel_ioctl(substream, SNDRV_PCM_IOCTL_PREPARE, NULL);
	if (result < 0) {
		ERROR(snd->card,
			"Preparing sound card failed: %d\n", (int)result);
		kfree(params);
		return result;
	}

	/* Store the hardware parameters */
	snd->access = params_access(params);
	snd->format = params_format(params);
	snd->channels = params_channels(params);
	snd->rate = params_rate(params);

	kfree(params);

	INFO(snd->card,
		"Hardware params: access %x, format %x, channels %d, rate %d\n",
		snd->access, snd->format, snd->channels, snd->rate);

	return 0;
}