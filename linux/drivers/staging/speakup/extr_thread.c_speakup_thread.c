#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct bleep {scalar_t__ jiffies; scalar_t__ freq; scalar_t__ active; } ;
struct TYPE_5__ {int /*<<< orphan*/  spinlock; scalar_t__ flushing; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* catch_up ) (TYPE_1__*) ;scalar_t__ alive; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kd_mksound (scalar_t__,scalar_t__) ; 
 scalar_t__ kthread_should_stop () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  speakup_event ; 
 TYPE_3__ speakup_info ; 
 int /*<<< orphan*/  speakup_start_ttys () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spk_mutex ; 
 struct bleep spk_unprocessed_sound ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 TYPE_1__* synth ; 
 int /*<<< orphan*/  synth_buffer_empty () ; 
 int /*<<< orphan*/  wait ; 

int speakup_thread(void *data)
{
	unsigned long flags;
	int should_break;
	struct bleep our_sound;

	our_sound.active = 0;
	our_sound.freq = 0;
	our_sound.jiffies = 0;

	mutex_lock(&spk_mutex);
	while (1) {
		DEFINE_WAIT(wait);

		while (1) {
			spin_lock_irqsave(&speakup_info.spinlock, flags);
			our_sound = spk_unprocessed_sound;
			spk_unprocessed_sound.active = 0;
			prepare_to_wait(&speakup_event, &wait,
					TASK_INTERRUPTIBLE);
			should_break = kthread_should_stop() ||
				our_sound.active ||
				(synth && synth->catch_up && synth->alive &&
					(speakup_info.flushing ||
					!synth_buffer_empty()));
			spin_unlock_irqrestore(&speakup_info.spinlock, flags);
			if (should_break)
				break;
			mutex_unlock(&spk_mutex);
			schedule();
			mutex_lock(&spk_mutex);
		}
		finish_wait(&speakup_event, &wait);
		if (kthread_should_stop())
			break;

		if (our_sound.active)
			kd_mksound(our_sound.freq, our_sound.jiffies);
		if (synth && synth->catch_up && synth->alive) {
			/*
			 * It is up to the callee to take the lock, so that it
			 * can sleep whenever it likes
			 */
			synth->catch_up(synth);
		}

		speakup_start_ttys();
	}
	mutex_unlock(&spk_mutex);
	return 0;
}