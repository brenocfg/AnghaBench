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
struct tty_audit_buf {scalar_t__ valid; scalar_t__ icanon; int /*<<< orphan*/  dev; int /*<<< orphan*/  mutex; void* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int N_TTY_BUF_SIZE ; 
 int /*<<< orphan*/  kfree (struct tty_audit_buf*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct tty_audit_buf *tty_audit_buf_alloc(void)
{
	struct tty_audit_buf *buf;

	buf = kmalloc(sizeof(*buf), GFP_KERNEL);
	if (!buf)
		goto err;
	buf->data = kmalloc(N_TTY_BUF_SIZE, GFP_KERNEL);
	if (!buf->data)
		goto err_buf;
	mutex_init(&buf->mutex);
	buf->dev = MKDEV(0, 0);
	buf->icanon = 0;
	buf->valid = 0;
	return buf;

err_buf:
	kfree(buf);
err:
	return NULL;
}