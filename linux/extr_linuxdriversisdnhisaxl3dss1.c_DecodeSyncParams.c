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

__attribute__((used)) static u_char
DecodeSyncParams(u_char si2, u_char info)
{
	info &= 0x7f;
	switch (info) {
	case 40:	// bit/s negotiation failed  ai := 165 not 175!

		return si2 + 15;
	case 15:	// 56000 bit/s failed, ai := 0 not 169 !

		return si2 + 9;
	case 14:	// 48000 bit/s

		return si2 + 8;
	case 11:	// 19200 bit/s

		return si2 + 7;
	case 9:	// 14400 bit/s

		return si2 + 6;
	case 8:	// 9600  bit/s

		return si2 + 5;
	case 5:	// 4800  bit/s

		return si2 + 4;
	case 3:	// 2400  bit/s

		return si2 + 3;
	case 23:	// 75/1200 bit/s

		return si2 + 2;
	case 24:	// 1200/75 bit/s

		return si2 + 1;
	default:	// 1200 bit/s

		return si2;
	}
}