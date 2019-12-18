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
struct snd_cobalt_card {scalar_t__ alsa_record_cnt; struct cobalt_stream* s; } ;
struct cobalt_stream {int /*<<< orphan*/  q; } ;

/* Variables and functions */
 struct snd_cobalt_card* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  vb2_thread_stop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_cobalt_pcm_capture_close(struct snd_pcm_substream *substream)
{
	struct snd_cobalt_card *cobsc = snd_pcm_substream_chip(substream);
	struct cobalt_stream *s = cobsc->s;

	cobsc->alsa_record_cnt--;
	if (cobsc->alsa_record_cnt == 0)
		vb2_thread_stop(&s->q);
	return 0;
}