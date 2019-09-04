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
struct radio_isa_card {int dummy; } ;

/* Variables and functions */
 int GEMTEK_NS ; 
 int /*<<< orphan*/  SHORT_DELAY ; 
 int inb_p (int) ; 
 int /*<<< orphan*/  outb_p (int,int) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool gemtek_probe(struct radio_isa_card *isa, int io)
{
	int i, q;

	q = inb_p(io);	/* Read bus contents before probing. */
	/* Try to turn on CE, CK and DA respectively and check if card responds
	   properly. */
	for (i = 0; i < 3; ++i) {
		outb_p(1 << i, io);
		udelay(SHORT_DELAY);

		if ((inb_p(io) & ~GEMTEK_NS) != (0x17 | (1 << (i + 5))))
			return false;
	}
	outb_p(q >> 5, io);	/* Write bus contents back. */
	udelay(SHORT_DELAY);
	return true;
}