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
struct tty_ldisc {TYPE_1__* ops; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int /*<<< orphan*/  __poll_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* poll ) (struct tty_struct*,struct file*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  file_inode (struct file*) ; 
 struct tty_struct* file_tty (struct file*) ; 
 int /*<<< orphan*/  hung_up_tty_poll (struct file*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct tty_struct*,struct file*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_ldisc_deref (struct tty_ldisc*) ; 
 struct tty_ldisc* tty_ldisc_ref_wait (struct tty_struct*) ; 
 scalar_t__ tty_paranoia_check (struct tty_struct*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static __poll_t tty_poll(struct file *filp, poll_table *wait)
{
	struct tty_struct *tty = file_tty(filp);
	struct tty_ldisc *ld;
	__poll_t ret = 0;

	if (tty_paranoia_check(tty, file_inode(filp), "tty_poll"))
		return 0;

	ld = tty_ldisc_ref_wait(tty);
	if (!ld)
		return hung_up_tty_poll(filp, wait);
	if (ld->ops->poll)
		ret = ld->ops->poll(tty, filp, wait);
	tty_ldisc_deref(ld);
	return ret;
}