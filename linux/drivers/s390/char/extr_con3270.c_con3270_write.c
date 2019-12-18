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
struct console {int dummy; } ;
struct TYPE_4__ {scalar_t__ cols; int /*<<< orphan*/  lock; scalar_t__ dev; } ;
struct con3270 {TYPE_2__ view; int /*<<< orphan*/  timer; scalar_t__ nr_up; TYPE_1__* cline; } ;
struct TYPE_3__ {scalar_t__ len; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  con3270_cline_add (struct con3270*) ; 
 int /*<<< orphan*/  con3270_cline_end (struct con3270*) ; 
 int /*<<< orphan*/  con3270_cline_insert (struct con3270*,unsigned char) ; 
 int /*<<< orphan*/  con3270_set_timer (struct con3270*,int) ; 
 struct con3270* condev ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  timer_pending (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
con3270_write(struct console *co, const char *str, unsigned int count)
{
	struct con3270 *cp;
	unsigned long flags;
	unsigned char c;

	cp = condev;
	spin_lock_irqsave(&cp->view.lock, flags);
	while (count-- > 0) {
		c = *str++;
		if (cp->cline->len == 0)
			con3270_cline_add(cp);
		if (c != '\n')
			con3270_cline_insert(cp, c);
		if (c == '\n' || cp->cline->len >= cp->view.cols)
			con3270_cline_end(cp);
	}
	/* Setup timer to output current console buffer after 1/10 second */
	cp->nr_up = 0;
	if (cp->view.dev && !timer_pending(&cp->timer))
		con3270_set_timer(cp, HZ/10);
	spin_unlock_irqrestore(&cp->view.lock,flags);
}