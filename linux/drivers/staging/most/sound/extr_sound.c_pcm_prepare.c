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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; struct channel* private_data; } ;
struct snd_pcm_runtime {int /*<<< orphan*/  format; } ;
struct most_channel_config {scalar_t__ direction; } ;
struct channel {scalar_t__ buffer_pos; scalar_t__ period_pos; int /*<<< orphan*/ * copy_fn; struct most_channel_config* cfg; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ MOST_CH_TX ; 
 int /*<<< orphan*/ * alsa_to_most_copy16 ; 
 int /*<<< orphan*/ * alsa_to_most_copy24 ; 
 int /*<<< orphan*/ * alsa_to_most_copy32 ; 
 int /*<<< orphan*/ * alsa_to_most_memcpy ; 
 int /*<<< orphan*/ * most_to_alsa_copy16 ; 
 int /*<<< orphan*/ * most_to_alsa_copy24 ; 
 int /*<<< orphan*/ * most_to_alsa_copy32 ; 
 int /*<<< orphan*/ * most_to_alsa_memcpy ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ snd_pcm_format_big_endian (int /*<<< orphan*/ ) ; 
 int snd_pcm_format_physical_width (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pcm_prepare(struct snd_pcm_substream *substream)
{
	struct channel *channel = substream->private_data;
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct most_channel_config *cfg = channel->cfg;
	int width = snd_pcm_format_physical_width(runtime->format);

	channel->copy_fn = NULL;

	if (cfg->direction == MOST_CH_TX) {
		if (snd_pcm_format_big_endian(runtime->format) || width == 8)
			channel->copy_fn = alsa_to_most_memcpy;
		else if (width == 16)
			channel->copy_fn = alsa_to_most_copy16;
		else if (width == 24)
			channel->copy_fn = alsa_to_most_copy24;
		else if (width == 32)
			channel->copy_fn = alsa_to_most_copy32;
	} else {
		if (snd_pcm_format_big_endian(runtime->format) || width == 8)
			channel->copy_fn = most_to_alsa_memcpy;
		else if (width == 16)
			channel->copy_fn = most_to_alsa_copy16;
		else if (width == 24)
			channel->copy_fn = most_to_alsa_copy24;
		else if (width == 32)
			channel->copy_fn = most_to_alsa_copy32;
	}

	if (!channel->copy_fn) {
		pr_err("unsupported format\n");
		return -EINVAL;
	}

	channel->period_pos = 0;
	channel->buffer_pos = 0;

	return 0;
}