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
struct snd_pcm_runtime {struct cobalt_stream* private_data; int /*<<< orphan*/  hw; } ;
struct snd_cobalt_card {int alsa_playback_cnt; struct snd_pcm_substream* playback_pcm_substream; struct cobalt_stream* s; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct cobalt_stream {TYPE_1__ vdev; int /*<<< orphan*/  q; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_PERIODS ; 
 int /*<<< orphan*/  alsa_pb_fnc ; 
 int /*<<< orphan*/  snd_cobalt_playback ; 
 int /*<<< orphan*/  snd_pcm_hw_constraint_integer (struct snd_pcm_runtime*,int /*<<< orphan*/ ) ; 
 struct snd_cobalt_card* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int vb2_thread_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct cobalt_stream*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_cobalt_pcm_playback_open(struct snd_pcm_substream *substream)
{
	struct snd_cobalt_card *cobsc = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct cobalt_stream *s = cobsc->s;

	runtime->hw = snd_cobalt_playback;
	snd_pcm_hw_constraint_integer(runtime, SNDRV_PCM_HW_PARAM_PERIODS);
	cobsc->playback_pcm_substream = substream;
	runtime->private_data = s;
	cobsc->alsa_playback_cnt++;
	if (cobsc->alsa_playback_cnt == 1) {
		int rc;

		rc = vb2_thread_start(&s->q, alsa_pb_fnc, s, s->vdev.name);
		if (rc) {
			cobsc->alsa_playback_cnt--;
			return rc;
		}
	}

	return 0;
}