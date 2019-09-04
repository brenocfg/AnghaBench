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
struct v4l2_device {int dummy; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_ivtv_card {struct v4l2_device* v4l2_dev; } ;
struct ivtv_stream {int /*<<< orphan*/  s_flags; } ;
struct ivtv {int /*<<< orphan*/ * pcm_announce_callback; struct ivtv_stream* streams; } ;

/* Variables and functions */
 size_t IVTV_ENC_STREAM_TYPE_PCM ; 
 int /*<<< orphan*/  IVTV_F_S_STREAMING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ivtv_release_stream (struct ivtv_stream*) ; 
 int /*<<< orphan*/  ivtv_stop_v4l2_encode_stream (struct ivtv_stream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ivtv_lock (struct snd_ivtv_card*) ; 
 int /*<<< orphan*/  snd_ivtv_unlock (struct snd_ivtv_card*) ; 
 struct snd_ivtv_card* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 struct ivtv* to_ivtv (struct v4l2_device*) ; 

__attribute__((used)) static int snd_ivtv_pcm_capture_close(struct snd_pcm_substream *substream)
{
	struct snd_ivtv_card *itvsc = snd_pcm_substream_chip(substream);
	struct v4l2_device *v4l2_dev = itvsc->v4l2_dev;
	struct ivtv *itv = to_ivtv(v4l2_dev);
	struct ivtv_stream *s;

	/* Instruct the ivtv to stop sending packets */
	snd_ivtv_lock(itvsc);
	s = &itv->streams[IVTV_ENC_STREAM_TYPE_PCM];
	ivtv_stop_v4l2_encode_stream(s, 0);
	clear_bit(IVTV_F_S_STREAMING, &s->s_flags);

	ivtv_release_stream(s);

	itv->pcm_announce_callback = NULL;
	snd_ivtv_unlock(itvsc);

	return 0;
}