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
struct tty_struct {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  work; int /*<<< orphan*/  tty; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  WORK_CPU_UNBOUND ; 
 scalar_t__ cmpxchg (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct tty_struct*) ; 
 int /*<<< orphan*/  schedule_work_on (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__ speakup_paste_work ; 
 int /*<<< orphan*/  tty_kref_get (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_kref_put (struct tty_struct*) ; 

int speakup_paste_selection(struct tty_struct *tty)
{
	tty_kref_get(tty);
	if (cmpxchg(&speakup_paste_work.tty, NULL, tty)) {
		tty_kref_put(tty);
		return -EBUSY;
	}

	schedule_work_on(WORK_CPU_UNBOUND, &speakup_paste_work.work);
	return 0;
}