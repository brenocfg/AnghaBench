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
struct tty_struct {TYPE_1__* ops; int /*<<< orphan*/  flags; } ;
struct serport {struct tty_struct* tty; int /*<<< orphan*/  flags; } ;
struct serdev_controller {int dummy; } ;
struct TYPE_2__ {int (* write ) (struct tty_struct*,unsigned char const*,size_t) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SERPORT_ACTIVE ; 
 int /*<<< orphan*/  TTY_DO_WRITE_WAKEUP ; 
 struct serport* serdev_controller_get_drvdata (struct serdev_controller*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub1 (struct tty_struct*,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ttyport_write_buf(struct serdev_controller *ctrl, const unsigned char *data, size_t len)
{
	struct serport *serport = serdev_controller_get_drvdata(ctrl);
	struct tty_struct *tty = serport->tty;

	if (!test_bit(SERPORT_ACTIVE, &serport->flags))
		return 0;

	set_bit(TTY_DO_WRITE_WAKEUP, &tty->flags);
	return tty->ops->write(serport->tty, data, len);
}