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
typedef  unsigned char u8 ;
struct gameport {int dummy; } ;

/* Variables and functions */
 int GUILLEMOT_MAX_LENGTH ; 
 int /*<<< orphan*/  GUILLEMOT_MAX_START ; 
 int /*<<< orphan*/  GUILLEMOT_MAX_STROBE ; 
 unsigned char gameport_read (struct gameport*) ; 
 unsigned int gameport_time (struct gameport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gameport_trigger (struct gameport*) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

__attribute__((used)) static int guillemot_read_packet(struct gameport *gameport, u8 *data)
{
	unsigned long flags;
	unsigned char u, v;
	unsigned int t, s;
	int i;

	for (i = 0; i < GUILLEMOT_MAX_LENGTH; i++)
		data[i] = 0;

	i = 0;
	t = gameport_time(gameport, GUILLEMOT_MAX_START);
	s = gameport_time(gameport, GUILLEMOT_MAX_STROBE);

	local_irq_save(flags);
	gameport_trigger(gameport);
	v = gameport_read(gameport);

	while (t > 0 && i < GUILLEMOT_MAX_LENGTH * 8) {
		t--;
		u = v; v = gameport_read(gameport);
		if (v & ~u & 0x10) {
			data[i >> 3] |= ((v >> 5) & 1) << (i & 7);
			i++;
			t = s;
		}
	}

	local_irq_restore(flags);

	return i;
}