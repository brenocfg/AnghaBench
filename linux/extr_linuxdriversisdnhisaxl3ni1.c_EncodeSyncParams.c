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
EncodeSyncParams(u_char si2, u_char ai)
{

	switch (si2) {
	case 0:
		return ai + 2;	// 1200 bit/s

	case 1:
		return ai + 24;		// 1200/75 bit/s

	case 2:
		return ai + 23;		// 75/1200 bit/s

	case 3:
		return ai + 3;	// 2400 bit/s

	case 4:
		return ai + 5;	// 4800 bit/s

	case 5:
		return ai + 8;	// 9600 bit/s

	case 6:
		return ai + 9;	// 14400 bit/s

	case 7:
		return ai + 11;		// 19200 bit/s

	case 8:
		return ai + 14;		// 48000 bit/s

	case 9:
		return ai + 15;		// 56000 bit/s

	case 15:
		return ai + 40;		// negotiate bit/s

	default:
		break;
	}
	return ai;
}