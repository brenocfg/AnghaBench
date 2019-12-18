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
struct TYPE_4__ {int /*<<< orphan*/  depth; } ;
struct cx18_stream {scalar_t__ type; int /*<<< orphan*/  name; int /*<<< orphan*/  waitq; TYPE_2__ q_full; int /*<<< orphan*/  s_flags; struct cx18* cx; } ;
struct cx18_mdl {scalar_t__ readpos; scalar_t__ bytesused; int /*<<< orphan*/  m_flags; } ;
struct TYPE_3__ {struct cx18_mdl sliced_mpeg_mdl; } ;
struct cx18 {TYPE_1__ vbi; scalar_t__ dualwatch_jiffies; struct cx18_stream* streams; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX18_DEBUG_INFO (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ CX18_ENC_STREAM_TYPE_MPG ; 
 size_t CX18_ENC_STREAM_TYPE_VBI ; 
 int /*<<< orphan*/  CX18_F_M_NEED_SWAP ; 
 int /*<<< orphan*/  CX18_F_S_APPL_IO ; 
 int /*<<< orphan*/  CX18_F_S_INTERNAL_USE ; 
 int /*<<< orphan*/  CX18_F_S_STREAMING ; 
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int EAGAIN ; 
 int EINTR ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 struct cx18_mdl* cx18_dequeue (struct cx18_stream*,TYPE_2__*) ; 
 int /*<<< orphan*/  cx18_dualwatch (struct cx18*) ; 
 int /*<<< orphan*/  cx18_mdl_swap (struct cx18_mdl*) ; 
 int /*<<< orphan*/  cx18_process_vbi_data (struct cx18*,struct cx18_mdl*,scalar_t__) ; 
 int /*<<< orphan*/  cx18_stream_put_mdl_fw (struct cx18_stream*,struct cx18_mdl*) ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule () ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static struct cx18_mdl *cx18_get_mdl(struct cx18_stream *s, int non_block,
				     int *err)
{
	struct cx18 *cx = s->cx;
	struct cx18_stream *s_vbi = &cx->streams[CX18_ENC_STREAM_TYPE_VBI];
	struct cx18_mdl *mdl;
	DEFINE_WAIT(wait);

	*err = 0;
	while (1) {
		if (s->type == CX18_ENC_STREAM_TYPE_MPG) {
			/* Process pending program updates and VBI data */
			if (time_after(jiffies, cx->dualwatch_jiffies + msecs_to_jiffies(1000))) {
				cx->dualwatch_jiffies = jiffies;
				cx18_dualwatch(cx);
			}
			if (test_bit(CX18_F_S_INTERNAL_USE, &s_vbi->s_flags) &&
			    !test_bit(CX18_F_S_APPL_IO, &s_vbi->s_flags)) {
				while ((mdl = cx18_dequeue(s_vbi,
							   &s_vbi->q_full))) {
					/* byteswap and process VBI data */
					cx18_process_vbi_data(cx, mdl,
							      s_vbi->type);
					cx18_stream_put_mdl_fw(s_vbi, mdl);
				}
			}
			mdl = &cx->vbi.sliced_mpeg_mdl;
			if (mdl->readpos != mdl->bytesused)
				return mdl;
		}

		/* do we have new data? */
		mdl = cx18_dequeue(s, &s->q_full);
		if (mdl) {
			if (!test_and_clear_bit(CX18_F_M_NEED_SWAP,
						&mdl->m_flags))
				return mdl;
			if (s->type == CX18_ENC_STREAM_TYPE_MPG)
				/* byteswap MPG data */
				cx18_mdl_swap(mdl);
			else {
				/* byteswap and process VBI data */
				cx18_process_vbi_data(cx, mdl, s->type);
			}
			return mdl;
		}

		/* return if end of stream */
		if (!test_bit(CX18_F_S_STREAMING, &s->s_flags)) {
			CX18_DEBUG_INFO("EOS %s\n", s->name);
			return NULL;
		}

		/* return if file was opened with O_NONBLOCK */
		if (non_block) {
			*err = -EAGAIN;
			return NULL;
		}

		/* wait for more data to arrive */
		prepare_to_wait(&s->waitq, &wait, TASK_INTERRUPTIBLE);
		/* New buffers might have become available before we were added
		   to the waitqueue */
		if (!atomic_read(&s->q_full.depth))
			schedule();
		finish_wait(&s->waitq, &wait);
		if (signal_pending(current)) {
			/* return if a signal was received */
			CX18_DEBUG_INFO("User stopped %s\n", s->name);
			*err = -EINTR;
			return NULL;
		}
	}
}