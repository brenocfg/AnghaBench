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
 int TMDC_MAX_LENGTH ; 
 int /*<<< orphan*/  TMDC_MAX_START ; 
 int /*<<< orphan*/  TMDC_MAX_STROBE ; 
 int gameport_read (struct gameport*) ; 
 int gameport_time (struct gameport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gameport_trigger (struct gameport*) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

__attribute__((used)) static int tmdc_read_packet(struct gameport *gameport, unsigned char data[2][TMDC_MAX_LENGTH])
{
	unsigned char u, v, w, x;
	unsigned long flags;
	int i[2], j[2], t[2], p, k;

	p = gameport_time(gameport, TMDC_MAX_STROBE);

	for (k = 0; k < 2; k++) {
		t[k] = gameport_time(gameport, TMDC_MAX_START);
		i[k] = j[k] = 0;
	}

	local_irq_save(flags);
	gameport_trigger(gameport);

	w = gameport_read(gameport) >> 4;

	do {
		x = w;
		w = gameport_read(gameport) >> 4;

		for (k = 0, v = w, u = x; k < 2; k++, v >>= 2, u >>= 2) {
			if (~v & u & 2) {
				if (t[k] <= 0 || i[k] >= TMDC_MAX_LENGTH) continue;
				t[k] = p;
				if (j[k] == 0) {				 /* Start bit */
					if (~v & 1) t[k] = 0;
					data[k][i[k]] = 0; j[k]++; continue;
				}
				if (j[k] == 9) {				/* Stop bit */
					if (v & 1) t[k] = 0;
					j[k] = 0; i[k]++; continue;
				}
				data[k][i[k]] |= (~v & 1) << (j[k]++ - 1);	/* Data bit */
			}
			t[k]--;
		}
	} while (t[0] > 0 || t[1] > 0);

	local_irq_restore(flags);

	return (i[0] == TMDC_MAX_LENGTH) | ((i[1] == TMDC_MAX_LENGTH) << 1);
}