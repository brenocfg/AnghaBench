#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct tty_audit_buf {scalar_t__ valid; struct tty_audit_buf* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  kfree (struct tty_audit_buf*) ; 

__attribute__((used)) static void tty_audit_buf_free(struct tty_audit_buf *buf)
{
	WARN_ON(buf->valid != 0);
	kfree(buf->data);
	kfree(buf);
}