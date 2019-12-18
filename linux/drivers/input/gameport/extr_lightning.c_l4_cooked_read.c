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
struct l4 {int port; } ;
struct gameport {struct l4* port_data; } ;

/* Variables and functions */
 int L4_BUSY ; 
 int /*<<< orphan*/  L4_PORT ; 
 int L4_SELECT_ANALOG ; 
 int L4_SELECT_DIGITAL ; 
 int inb (int /*<<< orphan*/ ) ; 
 scalar_t__ l4_wait_ready () ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int l4_cooked_read(struct gameport *gameport, int *axes, int *buttons)
{
	struct l4 *l4 = gameport->port_data;
	unsigned char status;
	int i, result = -1;

	outb(L4_SELECT_ANALOG, L4_PORT);
	outb(L4_SELECT_DIGITAL + (l4->port >> 2), L4_PORT);

	if (inb(L4_PORT) & L4_BUSY) goto fail;
	outb(l4->port & 3, L4_PORT);

	if (l4_wait_ready()) goto fail;
	status = inb(L4_PORT);

	for (i = 0; i < 4; i++)
		if (status & (1 << i)) {
			if (l4_wait_ready()) goto fail;
			axes[i] = inb(L4_PORT);
			if (axes[i] > 252) axes[i] = -1;
		}

	if (status & 0x10) {
		if (l4_wait_ready()) goto fail;
		*buttons = inb(L4_PORT) & 0x0f;
	}

	result = 0;

fail:	outb(L4_SELECT_ANALOG, L4_PORT);
	return result;
}