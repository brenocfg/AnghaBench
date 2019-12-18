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
struct TYPE_3__ {struct tty_audit_buf* tty_audit_buf; } ;

/* Variables and functions */
 struct tty_audit_buf* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESRCH ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 TYPE_2__* current ; 

__attribute__((used)) static struct tty_audit_buf *tty_audit_buf_ref(void)
{
	struct tty_audit_buf *buf;

	buf = current->signal->tty_audit_buf;
	WARN_ON(buf == ERR_PTR(-ESRCH));
	return buf;
}