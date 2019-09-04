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
typedef  unsigned int u8 ;

/* Variables and functions */
 unsigned int calc_parity (unsigned int) ; 
 unsigned int* hamming ; 
 int /*<<< orphan*/  memcpy (unsigned int*,char*,int) ; 
 int /*<<< orphan*/  memset (unsigned int*,int,int) ; 

__attribute__((used)) static void vivid_vbi_gen_teletext(u8 *packet, unsigned line, unsigned frame)
{
	unsigned offset = 2;
	unsigned i;

	packet[0] = hamming[1 + ((line & 1) << 3)];
	packet[1] = hamming[line >> 1];
	memset(packet + 2, 0x20, 40);
	if (line == 0) {
		/* subcode */
		packet[2] = hamming[frame % 10];
		packet[3] = hamming[frame / 10];
		packet[4] = hamming[0];
		packet[5] = hamming[0];
		packet[6] = hamming[0];
		packet[7] = hamming[0];
		packet[8] = hamming[0];
		packet[9] = hamming[1];
		offset = 10;
	}
	packet += offset;
	memcpy(packet, "Page: 100 Row: 10", 17);
	packet[7] = '0' + frame / 10;
	packet[8] = '0' + frame % 10;
	packet[15] = '0' + line / 10;
	packet[16] = '0' + line % 10;
	for (i = 0; i < 42 - offset; i++)
		packet[i] = calc_parity(packet[i]);
}