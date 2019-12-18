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
struct timer_list {int dummy; } ;
struct TYPE_4__ {void* expires; } ;
struct fza_private {int timer_state; TYPE_2__ reset_timer; TYPE_1__* regs; int /*<<< orphan*/  int_mask; int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int /*<<< orphan*/  int_mask; int /*<<< orphan*/  reset; } ;

/* Variables and functions */
 int /*<<< orphan*/  FZA_RESET_CLR ; 
 int /*<<< orphan*/  FZA_RESET_INIT ; 
 int HZ ; 
 int /*<<< orphan*/  add_timer (TYPE_2__*) ; 
 struct fza_private* fp ; 
 struct fza_private* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 void* jiffies ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readw_o (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reset_timer ; 
 int /*<<< orphan*/  writew_o (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writew_u (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fza_reset_timer(struct timer_list *t)
{
	struct fza_private *fp = from_timer(fp, t, reset_timer);

	if (!fp->timer_state) {
		pr_err("%s: RESET timed out!\n", fp->name);
		pr_info("%s: trying harder...\n", fp->name);

		/* Assert the board reset. */
		writew_o(FZA_RESET_INIT, &fp->regs->reset);
		readw_o(&fp->regs->reset);		/* Synchronize. */

		fp->timer_state = 1;
		fp->reset_timer.expires = jiffies + HZ;
	} else {
		/* Clear the board reset. */
		writew_u(FZA_RESET_CLR, &fp->regs->reset);

		/* Enable all interrupt events we handle. */
		writew_o(fp->int_mask, &fp->regs->int_mask);
		readw_o(&fp->regs->int_mask);		/* Synchronize. */

		fp->timer_state = 0;
		fp->reset_timer.expires = jiffies + 45 * HZ;
	}
	add_timer(&fp->reset_timer);
}