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
struct tty_struct {scalar_t__ index; TYPE_1__* driver; } ;
typedef  scalar_t__ dev_t ;
struct TYPE_2__ {int /*<<< orphan*/  minor_start; int /*<<< orphan*/  major; } ;

/* Variables and functions */
 scalar_t__ MKDEV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ audit_enabled ; 
 int /*<<< orphan*/  tty_audit_log (char*,scalar_t__,char*,int) ; 
 scalar_t__ tty_audit_push () ; 

void tty_audit_tiocsti(struct tty_struct *tty, char ch)
{
	dev_t dev;

	dev = MKDEV(tty->driver->major, tty->driver->minor_start) + tty->index;
	if (tty_audit_push())
		return;

	if (audit_enabled)
		tty_audit_log("ioctl=TIOCSTI", dev, &ch, 1);
}