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
typedef  int /*<<< orphan*/  u8 ;
struct ivtv_stream {int /*<<< orphan*/  q_free; int /*<<< orphan*/  q_full; int /*<<< orphan*/  q_io; } ;
struct ivtv_buffer {scalar_t__ readpos; scalar_t__ bytesused; scalar_t__ buf; } ;
struct ivtv {int /*<<< orphan*/  alsa; int /*<<< orphan*/  (* pcm_announce_callback ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ;struct ivtv_stream* streams; } ;

/* Variables and functions */
 size_t IVTV_ENC_STREAM_TYPE_PCM ; 
 struct ivtv_buffer* ivtv_dequeue (struct ivtv_stream*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ivtv_enqueue (struct ivtv_stream*,struct ivtv_buffer*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void ivtv_pcm_work_handler(struct ivtv *itv)
{
	struct ivtv_stream *s = &itv->streams[IVTV_ENC_STREAM_TYPE_PCM];
	struct ivtv_buffer *buf;

	/* Pass the PCM data to ivtv-alsa */

	while (1) {
		/*
		 * Users should not be using both the ALSA and V4L2 PCM audio
		 * capture interfaces at the same time.  If the user is doing
		 * this, there maybe a buffer in q_io to grab, use, and put
		 * back in rotation.
		 */
		buf = ivtv_dequeue(s, &s->q_io);
		if (buf == NULL)
			buf = ivtv_dequeue(s, &s->q_full);
		if (buf == NULL)
			break;

		if (buf->readpos < buf->bytesused)
			itv->pcm_announce_callback(itv->alsa,
				(u8 *)(buf->buf + buf->readpos),
				(size_t)(buf->bytesused - buf->readpos));

		ivtv_enqueue(s, buf, &s->q_free);
	}
}