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
typedef  int __u64 ;

/* Variables and functions */
 int COBRA_LENGTH ; 
 int COBRA_MAX_STROBE ; 
 unsigned char gameport_read (struct gameport*) ; 
 int gameport_time (struct gameport*,int) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

__attribute__((used)) static unsigned char cobra_read_packet(struct gameport *gameport, unsigned int *data)
{
	unsigned long flags;
	unsigned char u, v, w;
	__u64 buf[2];
	int r[2], t[2];
	int i, j, ret;

	int strobe = gameport_time(gameport, COBRA_MAX_STROBE);

	for (i = 0; i < 2; i++) {
		r[i] = buf[i] = 0;
		t[i] = COBRA_MAX_STROBE;
	}

	local_irq_save(flags);

	u = gameport_read(gameport);

	do {
		t[0]--; t[1]--;
		v = gameport_read(gameport);
		for (i = 0, w = u ^ v; i < 2 && w; i++, w >>= 2)
			if (w & 0x30) {
				if ((w & 0x30) < 0x30 && r[i] < COBRA_LENGTH && t[i] > 0) {
					buf[i] |= (__u64)((w >> 5) & 1) << r[i]++;
					t[i] = strobe;
					u = v;
				} else t[i] = 0;
			}
	} while (t[0] > 0 || t[1] > 0);

	local_irq_restore(flags);

	ret = 0;

	for (i = 0; i < 2; i++) {

		if (r[i] != COBRA_LENGTH) continue;

		for (j = 0; j < COBRA_LENGTH && (buf[i] & 0x04104107f) ^ 0x041041040; j++)
			buf[i] = (buf[i] >> 1) | ((__u64)(buf[i] & 1) << (COBRA_LENGTH - 1));

		if (j < COBRA_LENGTH) ret |= (1 << i);

		data[i] = ((buf[i] >>  7) & 0x000001f) | ((buf[i] >>  8) & 0x00003e0)
			| ((buf[i] >>  9) & 0x0007c00) | ((buf[i] >> 10) & 0x00f8000)
			| ((buf[i] >> 11) & 0x1f00000);

	}

	return ret;
}