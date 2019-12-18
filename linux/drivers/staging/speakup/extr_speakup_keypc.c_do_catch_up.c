#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  char u_char ;
struct TYPE_4__ {int value; } ;
struct TYPE_5__ {TYPE_1__ n; } ;
struct var_t {TYPE_2__ u; } ;
struct spk_synth {int /*<<< orphan*/  (* flush ) (struct spk_synth*) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  spinlock; scalar_t__ flushing; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY ; 
 int /*<<< orphan*/  FULL ; 
 int /*<<< orphan*/  JIFFY ; 
 char PROCSPEECH ; 
 char SPACE ; 
 int /*<<< orphan*/  SWAIT ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int jiffies ; 
 int /*<<< orphan*/  kthread_should_stop () ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  oops () ; 
 int /*<<< orphan*/  outb_p (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_timeout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 TYPE_3__ speakup_info ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct var_t* spk_get_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct spk_synth*) ; 
 scalar_t__ synth_buffer_empty () ; 
 char synth_buffer_getc () ; 
 int /*<<< orphan*/  synth_buffer_skip_nonlatin1 () ; 
 scalar_t__ synth_full () ; 
 int /*<<< orphan*/  synth_port ; 
 scalar_t__ synth_writable () ; 
 scalar_t__ time_after_eq (int,unsigned long) ; 

__attribute__((used)) static void do_catch_up(struct spk_synth *synth)
{
	u_char ch;
	int timeout;
	unsigned long flags;
	unsigned long jiff_max;
	struct var_t *jiffy_delta;
	struct var_t *delay_time;
	struct var_t *full_time;
	int delay_time_val;
	int full_time_val;
	int jiffy_delta_val;

	jiffy_delta = spk_get_var(JIFFY);
	delay_time = spk_get_var(DELAY);
	full_time = spk_get_var(FULL);
	spin_lock_irqsave(&speakup_info.spinlock, flags);
	jiffy_delta_val = jiffy_delta->u.n.value;
	spin_unlock_irqrestore(&speakup_info.spinlock, flags);

	jiff_max = jiffies + jiffy_delta_val;
	while (!kthread_should_stop()) {
		spin_lock_irqsave(&speakup_info.spinlock, flags);
		if (speakup_info.flushing) {
			speakup_info.flushing = 0;
			spin_unlock_irqrestore(&speakup_info.spinlock, flags);
			synth->flush(synth);
			continue;
		}
		synth_buffer_skip_nonlatin1();
		if (synth_buffer_empty()) {
			spin_unlock_irqrestore(&speakup_info.spinlock, flags);
			break;
		}
		set_current_state(TASK_INTERRUPTIBLE);
		full_time_val = full_time->u.n.value;
		spin_unlock_irqrestore(&speakup_info.spinlock, flags);
		if (synth_full()) {
			schedule_timeout(msecs_to_jiffies(full_time_val));
			continue;
		}
		set_current_state(TASK_RUNNING);
		timeout = 1000;
		while (synth_writable())
			if (--timeout <= 0)
				break;
		if (timeout <= 0) {
			oops();
			break;
		}
		spin_lock_irqsave(&speakup_info.spinlock, flags);
		ch = synth_buffer_getc();
		spin_unlock_irqrestore(&speakup_info.spinlock, flags);
		if (ch == '\n')
			ch = PROCSPEECH;
		outb_p(ch, synth_port);
		SWAIT;
		if (time_after_eq(jiffies, jiff_max) && (ch == SPACE)) {
			timeout = 1000;
			while (synth_writable())
				if (--timeout <= 0)
					break;
			if (timeout <= 0) {
				oops();
				break;
			}
			outb_p(PROCSPEECH, synth_port);
			spin_lock_irqsave(&speakup_info.spinlock, flags);
			jiffy_delta_val = jiffy_delta->u.n.value;
			delay_time_val = delay_time->u.n.value;
			spin_unlock_irqrestore(&speakup_info.spinlock, flags);
			schedule_timeout(msecs_to_jiffies(delay_time_val));
			jiff_max = jiffies + jiffy_delta_val;
		}
	}
	timeout = 1000;
	while (synth_writable())
		if (--timeout <= 0)
			break;
	if (timeout <= 0)
		oops();
	else
		outb_p(PROCSPEECH, synth_port);
}