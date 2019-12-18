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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int channels; int /*<<< orphan*/  format; int /*<<< orphan*/  rate; struct bcm2835_alsa_stream* private_data; } ;
struct bcm2835_chip {int spdif_status; } ;
struct TYPE_2__ {void* sw_buffer_size; void* hw_buffer_size; } ;
struct bcm2835_alsa_stream {int draining; int /*<<< orphan*/  interpolate_start; scalar_t__ period_offset; int /*<<< orphan*/  pos; int /*<<< orphan*/  period_size; void* buffer_size; TYPE_1__ pcm_indirect; } ;

/* Variables and functions */
 int IEC958_AES0_NONAUDIO ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int bcm2835_audio_set_params (struct bcm2835_alsa_stream*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_pcm_format_width (int /*<<< orphan*/ ) ; 
 void* snd_pcm_lib_buffer_bytes (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_pcm_lib_period_bytes (struct snd_pcm_substream*) ; 
 struct bcm2835_chip* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_bcm2835_pcm_prepare(struct snd_pcm_substream *substream)
{
	struct bcm2835_chip *chip = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct bcm2835_alsa_stream *alsa_stream = runtime->private_data;
	int channels;
	int err;

	/* notify the vchiq that it should enter spdif passthrough mode by
	 * setting channels=0 (see
	 * https://github.com/raspberrypi/linux/issues/528)
	 */
	if (chip->spdif_status & IEC958_AES0_NONAUDIO)
		channels = 0;
	else
		channels = runtime->channels;

	err = bcm2835_audio_set_params(alsa_stream, channels,
				       runtime->rate,
				       snd_pcm_format_width(runtime->format));
	if (err < 0)
		return err;

	memset(&alsa_stream->pcm_indirect, 0, sizeof(alsa_stream->pcm_indirect));

	alsa_stream->pcm_indirect.hw_buffer_size =
		alsa_stream->pcm_indirect.sw_buffer_size =
		snd_pcm_lib_buffer_bytes(substream);

	alsa_stream->buffer_size = snd_pcm_lib_buffer_bytes(substream);
	alsa_stream->period_size = snd_pcm_lib_period_bytes(substream);
	atomic_set(&alsa_stream->pos, 0);
	alsa_stream->period_offset = 0;
	alsa_stream->draining = false;
	alsa_stream->interpolate_start = ktime_get();

	return 0;
}