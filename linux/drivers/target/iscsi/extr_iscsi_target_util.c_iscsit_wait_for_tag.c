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
struct sbitmap_queue {struct sbq_wait_state* ws; } ;
struct se_session {struct sbitmap_queue sess_tag_pool; } ;
struct sbq_wait_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_SBQ_WAIT (int /*<<< orphan*/ ) ; 
 int TASK_RUNNING ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  sbitmap_finish_wait (struct sbitmap_queue*,struct sbq_wait_state*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sbitmap_prepare_to_wait (struct sbitmap_queue*,struct sbq_wait_state*,int /*<<< orphan*/ *,int) ; 
 int sbitmap_queue_get (struct sbitmap_queue*,int*) ; 
 int /*<<< orphan*/  schedule () ; 
 scalar_t__ signal_pending_state (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static int iscsit_wait_for_tag(struct se_session *se_sess, int state, int *cpup)
{
	int tag = -1;
	DEFINE_SBQ_WAIT(wait);
	struct sbq_wait_state *ws;
	struct sbitmap_queue *sbq;

	if (state == TASK_RUNNING)
		return tag;

	sbq = &se_sess->sess_tag_pool;
	ws = &sbq->ws[0];
	for (;;) {
		sbitmap_prepare_to_wait(sbq, ws, &wait, state);
		if (signal_pending_state(state, current))
			break;
		tag = sbitmap_queue_get(sbq, cpup);
		if (tag >= 0)
			break;
		schedule();
	}

	sbitmap_finish_wait(sbq, ws, &wait);
	return tag;
}