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
struct file {TYPE_1__* f_op; } ;
struct TYPE_2__ {scalar_t__ write; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGTTIN ; 
 int __tty_check_change (struct tty_struct*,int /*<<< orphan*/ ) ; 
 scalar_t__ redirected_tty_write ; 

__attribute__((used)) static int job_control(struct tty_struct *tty, struct file *file)
{
	/* Job control check -- must be done at start and after
	   every sleep (POSIX.1 7.1.1.4). */
	/* NOTE: not yet done after every sleep pending a thorough
	   check of the logic of this change. -- jlc */
	/* don't stop on /dev/console */
	if (file->f_op->write == redirected_tty_write)
		return 0;

	return __tty_check_change(tty, SIGTTIN);
}