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
struct TYPE_2__ {int /*<<< orphan*/  tty; int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 TYPE_1__ speakup_paste_work ; 
 int /*<<< orphan*/  tty_kref_put (struct tty_struct*) ; 
 struct tty_struct* xchg (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void speakup_cancel_paste(void)
{
	struct tty_struct *tty;

	cancel_work_sync(&speakup_paste_work.work);
	tty = xchg(&speakup_paste_work.tty, NULL);
	if (tty)
		tty_kref_put(tty);
}