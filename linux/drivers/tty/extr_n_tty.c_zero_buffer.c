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
typedef  int /*<<< orphan*/  u8 ;
struct tty_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  L_ECHO (struct tty_struct*) ; 
 int /*<<< orphan*/  L_ICANON (struct tty_struct*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void zero_buffer(struct tty_struct *tty, u8 *buffer, int size)
{
	bool icanon = !!L_ICANON(tty);
	bool no_echo = !L_ECHO(tty);

	if (icanon && no_echo)
		memset(buffer, 0x00, size);
}