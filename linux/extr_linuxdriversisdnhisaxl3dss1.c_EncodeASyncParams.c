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
typedef  int u_char ;

/* Variables and functions */

__attribute__((used)) static u_char *
EncodeASyncParams(u_char *p, u_char si2)
{				// 7c 06 88  90 21 42 00 bb

	p[0] = 0;
	p[1] = 0x40;		// Intermediate rate: 16 kbit/s jj 2000.02.19
	p[2] = 0x80;
	if (si2 & 32)		// 7 data bits

		p[2] += 16;
	else			// 8 data bits

		p[2] += 24;

	if (si2 & 16)		// 2 stop bits

		p[2] += 96;
	else			// 1 stop bit

		p[2] += 32;

	if (si2 & 8)		// even parity

		p[2] += 2;
	else			// no parity

		p[2] += 3;

	switch (si2 & 0x07) {
	case 0:
		p[0] = 66;	// 1200 bit/s

		break;
	case 1:
		p[0] = 88;	// 1200/75 bit/s

		break;
	case 2:
		p[0] = 87;	// 75/1200 bit/s

		break;
	case 3:
		p[0] = 67;	// 2400 bit/s

		break;
	case 4:
		p[0] = 69;	// 4800 bit/s

		break;
	case 5:
		p[0] = 72;	// 9600 bit/s

		break;
	case 6:
		p[0] = 73;	// 14400 bit/s

		break;
	case 7:
		p[0] = 75;	// 19200 bit/s

		break;
	}
	return p + 3;
}