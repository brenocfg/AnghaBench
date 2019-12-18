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
struct gameport {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GF2K_START ; 
 int /*<<< orphan*/  GF2K_STROBE ; 
 unsigned char gameport_read (struct gameport*) ; 
 unsigned int gameport_time (struct gameport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gameport_trigger (struct gameport*) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

__attribute__((used)) static int gf2k_read_packet(struct gameport *gameport, int length, char *data)
{
	unsigned char u, v;
	int i;
	unsigned int t, p;
	unsigned long flags;

	t = gameport_time(gameport, GF2K_START);
	p = gameport_time(gameport, GF2K_STROBE);

	i = 0;

	local_irq_save(flags);

	gameport_trigger(gameport);
	v = gameport_read(gameport);

	while (t > 0 && i < length) {
		t--; u = v;
		v = gameport_read(gameport);
		if (v & ~u & 0x10) {
			data[i++] = v >> 5;
			t = p;
		}
	}

	local_irq_restore(flags);

	return i;
}