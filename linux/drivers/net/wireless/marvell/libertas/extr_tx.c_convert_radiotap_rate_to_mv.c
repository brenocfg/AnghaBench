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
typedef  int u8 ;
typedef  int u32 ;

/* Variables and functions */

__attribute__((used)) static u32 convert_radiotap_rate_to_mv(u8 rate)
{
	switch (rate) {
	case 2:		/*   1 Mbps */
		return 0 | (1 << 4);
	case 4:		/*   2 Mbps */
		return 1 | (1 << 4);
	case 11:		/* 5.5 Mbps */
		return 2 | (1 << 4);
	case 22:		/*  11 Mbps */
		return 3 | (1 << 4);
	case 12:		/*   6 Mbps */
		return 4 | (1 << 4);
	case 18:		/*   9 Mbps */
		return 5 | (1 << 4);
	case 24:		/*  12 Mbps */
		return 6 | (1 << 4);
	case 36:		/*  18 Mbps */
		return 7 | (1 << 4);
	case 48:		/*  24 Mbps */
		return 8 | (1 << 4);
	case 72:		/*  36 Mbps */
		return 9 | (1 << 4);
	case 96:		/*  48 Mbps */
		return 10 | (1 << 4);
	case 108:		/*  54 Mbps */
		return 11 | (1 << 4);
	}
	return 0;
}