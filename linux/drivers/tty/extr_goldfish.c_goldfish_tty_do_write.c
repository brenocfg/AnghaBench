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
struct goldfish_tty {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  goldfish_tty_rw (struct goldfish_tty*,unsigned long,unsigned int,int) ; 
 struct goldfish_tty* goldfish_ttys ; 

__attribute__((used)) static void goldfish_tty_do_write(int line, const char *buf,
				  unsigned int count)
{
	struct goldfish_tty *qtty = &goldfish_ttys[line];
	unsigned long address = (unsigned long)(void *)buf;

	goldfish_tty_rw(qtty, address, count, 1);
}