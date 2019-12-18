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
struct snd_pcm {int /*<<< orphan*/  name; struct snd_cobalt_card* private_data; scalar_t__ info_flags; } ;
struct snd_cobalt_card {struct cobalt_stream* s; struct snd_card* sc; } ;
struct snd_card {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  gfp_flags; } ;
struct cobalt_stream {int /*<<< orphan*/  video_channel; int /*<<< orphan*/  is_output; TYPE_1__ q; struct cobalt* cobalt; } ;
struct cobalt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COBALT_SYS_CTRL_AUDIO_IPP_RESETN_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COBALT_SYS_CTRL_AUDIO_OPP_RESETN_BIT ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_CAPTURE ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  __GFP_ZERO ; 
 int /*<<< orphan*/  cobalt_err (char*,int) ; 
 int /*<<< orphan*/  cobalt_s_bit_sysctrl (struct cobalt*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  snd_cobalt_pcm_capture_ops ; 
 int /*<<< orphan*/  snd_cobalt_pcm_playback_ops ; 
 int snd_pcm_new (struct snd_card*,char*,int /*<<< orphan*/ ,int,int,struct snd_pcm**) ; 
 int /*<<< orphan*/  snd_pcm_set_ops (struct snd_pcm*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int) ; 

int snd_cobalt_pcm_create(struct snd_cobalt_card *cobsc)
{
	struct snd_pcm *sp;
	struct snd_card *sc = cobsc->sc;
	struct cobalt_stream *s = cobsc->s;
	struct cobalt *cobalt = s->cobalt;
	int ret;

	s->q.gfp_flags |= __GFP_ZERO;

	if (!s->is_output) {
		cobalt_s_bit_sysctrl(cobalt,
			COBALT_SYS_CTRL_AUDIO_IPP_RESETN_BIT(s->video_channel),
			0);
		mdelay(2);
		cobalt_s_bit_sysctrl(cobalt,
			COBALT_SYS_CTRL_AUDIO_IPP_RESETN_BIT(s->video_channel),
			1);
		mdelay(1);

		ret = snd_pcm_new(sc, "Cobalt PCM-In HDMI",
			0, /* PCM device 0, the only one for this card */
			0, /* 0 playback substreams */
			1, /* 1 capture substream */
			&sp);
		if (ret) {
			cobalt_err("snd_cobalt_pcm_create() failed for input with err %d\n",
				   ret);
			goto err_exit;
		}

		snd_pcm_set_ops(sp, SNDRV_PCM_STREAM_CAPTURE,
				&snd_cobalt_pcm_capture_ops);
		sp->info_flags = 0;
		sp->private_data = cobsc;
		strscpy(sp->name, "cobalt", sizeof(sp->name));
	} else {
		cobalt_s_bit_sysctrl(cobalt,
			COBALT_SYS_CTRL_AUDIO_OPP_RESETN_BIT, 0);
		mdelay(2);
		cobalt_s_bit_sysctrl(cobalt,
			COBALT_SYS_CTRL_AUDIO_OPP_RESETN_BIT, 1);
		mdelay(1);

		ret = snd_pcm_new(sc, "Cobalt PCM-Out HDMI",
			0, /* PCM device 0, the only one for this card */
			1, /* 0 playback substreams */
			0, /* 1 capture substream */
			&sp);
		if (ret) {
			cobalt_err("snd_cobalt_pcm_create() failed for output with err %d\n",
				   ret);
			goto err_exit;
		}

		snd_pcm_set_ops(sp, SNDRV_PCM_STREAM_PLAYBACK,
				&snd_cobalt_pcm_playback_ops);
		sp->info_flags = 0;
		sp->private_data = cobsc;
		strscpy(sp->name, "cobalt", sizeof(sp->name));
	}

	return 0;

err_exit:
	return ret;
}