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

/* Variables and functions */
 int /*<<< orphan*/  pr_alert (char*,int) ; 

__attribute__((used)) static u8 convert_mv_rate_to_radiotap(u8 rate)
{
	switch (rate) {
	case 0:		/*   1 Mbps */
		return 2;
	case 1:		/*   2 Mbps */
		return 4;
	case 2:		/* 5.5 Mbps */
		return 11;
	case 3:		/*  11 Mbps */
		return 22;
	/* case 4: reserved */
	case 5:		/*   6 Mbps */
		return 12;
	case 6:		/*   9 Mbps */
		return 18;
	case 7:		/*  12 Mbps */
		return 24;
	case 8:		/*  18 Mbps */
		return 36;
	case 9:		/*  24 Mbps */
		return 48;
	case 10:		/*  36 Mbps */
		return 72;
	case 11:		/*  48 Mbps */
		return 96;
	case 12:		/*  54 Mbps */
		return 108;
	}
	pr_alert("Invalid Marvell WLAN rate %i\n", rate);
	return 0;
}