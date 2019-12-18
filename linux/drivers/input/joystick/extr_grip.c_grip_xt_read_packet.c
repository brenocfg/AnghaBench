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
 unsigned int GRIP_MAX_BITS_XT ; 
 unsigned int GRIP_MAX_CHUNKS_XT ; 
 int /*<<< orphan*/  GRIP_STROBE_XT ; 
 int gameport_read (struct gameport*) ; 
 int gameport_time (struct gameport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

__attribute__((used)) static int grip_xt_read_packet(struct gameport *gameport, int shift, unsigned int *data)
{
	unsigned int i, j, buf, crc;
	unsigned char u, v, w;
	unsigned long flags;
	unsigned int t;
	char status;

	int strobe = gameport_time(gameport, GRIP_STROBE_XT);

	data[0] = data[1] = data[2] = data[3] = 0;
	status = buf = i = j = 0;
	t = strobe;

	local_irq_save(flags);

	v = w = (gameport_read(gameport) >> shift) & 3;

	do {
		t--;
		u = (gameport_read(gameport) >> shift) & 3;

		if (u ^ v) {

			if ((u ^ v) & 1) {
				buf = (buf << 1) | (u >> 1);
				t = strobe;
				i++;
			} else

			if ((((u ^ v) & (v ^ w)) >> 1) & ~(u | v | w) & 1) {
				if (i == 20) {
					crc = buf ^ (buf >> 7) ^ (buf >> 14);
					if (!((crc ^ (0x25cb9e70 >> ((crc >> 2) & 0x1c))) & 0xf)) {
						data[buf >> 18] = buf >> 4;
						status |= 1 << (buf >> 18);
					}
					j++;
				}
				t = strobe;
				buf = 0;
				i = 0;
			}
			w = v;
			v = u;
		}

	} while (status != 0xf && i < GRIP_MAX_BITS_XT && j < GRIP_MAX_CHUNKS_XT && t > 0);

	local_irq_restore(flags);

	return -(status != 0xf);
}