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
struct TYPE_2__ {struct tty_buffer* tail; } ;
struct tty_port {TYPE_1__ buf; } ;
struct tty_buffer {int flags; int /*<<< orphan*/  used; } ;

/* Variables and functions */
 int TTYB_NORMAL ; 
 char TTY_NORMAL ; 
 int /*<<< orphan*/  __tty_buffer_request_room (struct tty_port*,int,int) ; 
 unsigned char* char_buf_ptr (struct tty_buffer*,int /*<<< orphan*/ ) ; 
 char* flag_buf_ptr (struct tty_buffer*,int /*<<< orphan*/ ) ; 

int __tty_insert_flip_char(struct tty_port *port, unsigned char ch, char flag)
{
	struct tty_buffer *tb;
	int flags = (flag == TTY_NORMAL) ? TTYB_NORMAL : 0;

	if (!__tty_buffer_request_room(port, 1, flags))
		return 0;

	tb = port->buf.tail;
	if (~tb->flags & TTYB_NORMAL)
		*flag_buf_ptr(tb, tb->used) = flag;
	*char_buf_ptr(tb, tb->used++) = ch;

	return 1;
}