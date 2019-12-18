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
struct serport {int /*<<< orphan*/  tty_idx; int /*<<< orphan*/  flags; struct tty_struct* tty; } ;
struct serdev_controller {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* close ) (struct tty_struct*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SERPORT_ACTIVE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct serport* serdev_controller_get_drvdata (struct serdev_controller*) ; 
 int /*<<< orphan*/  stub1 (struct tty_struct*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_lock (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_release_struct (struct tty_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_unlock (struct tty_struct*) ; 

__attribute__((used)) static void ttyport_close(struct serdev_controller *ctrl)
{
	struct serport *serport = serdev_controller_get_drvdata(ctrl);
	struct tty_struct *tty = serport->tty;

	clear_bit(SERPORT_ACTIVE, &serport->flags);

	tty_lock(tty);
	if (tty->ops->close)
		tty->ops->close(tty, NULL);
	tty_unlock(tty);

	tty_release_struct(tty, serport->tty_idx);
}