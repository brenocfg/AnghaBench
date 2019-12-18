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

/* Variables and functions */
 int L4_BUSY ; 
 int L4_CMD_GETCAL ; 
 int /*<<< orphan*/  L4_PORT ; 
 int L4_SELECT_ANALOG ; 
 int L4_SELECT_DIGITAL ; 
 int inb (int /*<<< orphan*/ ) ; 
 scalar_t__ l4_wait_ready () ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int l4_getcal(int port, int *cal)
{
	int i, result = -1;

	outb(L4_SELECT_ANALOG, L4_PORT);
	outb(L4_SELECT_DIGITAL + (port >> 2), L4_PORT);
	if (inb(L4_PORT) & L4_BUSY)
		goto out;

	outb(L4_CMD_GETCAL, L4_PORT);
	if (l4_wait_ready())
		goto out;

	if (inb(L4_PORT) != L4_SELECT_DIGITAL + (port >> 2))
		goto out;

	if (l4_wait_ready())
		goto out;
        outb(port & 3, L4_PORT);

	for (i = 0; i < 4; i++) {
		if (l4_wait_ready())
			goto out;
		cal[i] = inb(L4_PORT);
	}

	result = 0;

out:	outb(L4_SELECT_ANALOG, L4_PORT);
	return result;
}