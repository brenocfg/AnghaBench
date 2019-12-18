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
struct tty_audit_buf {int dummy; } ;
struct TYPE_4__ {TYPE_1__* signal; } ;
struct TYPE_3__ {int /*<<< orphan*/  tty_audit_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESRCH ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  tty_audit_buf_free (struct tty_audit_buf*) ; 
 int /*<<< orphan*/  tty_audit_buf_push (struct tty_audit_buf*) ; 
 struct tty_audit_buf* xchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void tty_audit_exit(void)
{
	struct tty_audit_buf *buf;

	buf = xchg(&current->signal->tty_audit_buf, ERR_PTR(-ESRCH));
	if (!buf)
		return;

	tty_audit_buf_push(buf);
	tty_audit_buf_free(buf);
}