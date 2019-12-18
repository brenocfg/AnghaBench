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
 int /*<<< orphan*/  audit_log_lost (char*) ; 
 int /*<<< orphan*/ * cmpxchg (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct tty_audit_buf*) ; 
 TYPE_2__* current ; 
 struct tty_audit_buf* tty_audit_buf_alloc () ; 
 int /*<<< orphan*/  tty_audit_buf_free (struct tty_audit_buf*) ; 
 struct tty_audit_buf* tty_audit_buf_ref () ; 

__attribute__((used)) static struct tty_audit_buf *tty_audit_buf_get(void)
{
	struct tty_audit_buf *buf;

	buf = tty_audit_buf_ref();
	if (buf)
		return buf;

	buf = tty_audit_buf_alloc();
	if (buf == NULL) {
		audit_log_lost("out of memory in TTY auditing");
		return NULL;
	}

	/* Race to use this buffer, free it if another wins */
	if (cmpxchg(&current->signal->tty_audit_buf, NULL, buf) != NULL)
		tty_audit_buf_free(buf);
	return tty_audit_buf_ref();
}