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
 int /*<<< orphan*/  tty_encode_baud_rate (struct tty_struct*,int,int) ; 

__attribute__((used)) static void cypress_earthmate_init_termios(struct tty_struct *tty)
{
	tty_encode_baud_rate(tty, 4800, 4800);
}