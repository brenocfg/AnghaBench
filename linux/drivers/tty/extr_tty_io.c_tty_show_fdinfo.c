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
struct tty_struct {TYPE_1__* ops; } ;
struct seq_file {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* show_fdinfo ) (struct tty_struct*,struct seq_file*) ;} ;

/* Variables and functions */
 struct tty_struct* file_tty (struct file*) ; 
 int /*<<< orphan*/  stub1 (struct tty_struct*,struct seq_file*) ; 

__attribute__((used)) static void tty_show_fdinfo(struct seq_file *m, struct file *file)
{
	struct tty_struct *tty = file_tty(file);

	if (tty && tty->ops && tty->ops->show_fdinfo)
		tty->ops->show_fdinfo(tty, m);
}