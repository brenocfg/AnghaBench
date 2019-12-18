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
struct tty_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  n_tty_receive_char_inline (struct tty_struct*,unsigned char) ; 

__attribute__((used)) static void n_tty_receive_char(struct tty_struct *tty, unsigned char c)
{
	n_tty_receive_char_inline(tty, c);
}