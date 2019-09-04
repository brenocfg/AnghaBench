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
typedef  scalar_t__ u8 ;

/* Variables and functions */
 scalar_t__ CHIP_ID_YUKON_OP_2 ; 
 scalar_t__ CHIP_ID_YUKON_XL ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,scalar_t__) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 

__attribute__((used)) static const char *sky2_name(u8 chipid, char *buf, int sz)
{
	const char *name[] = {
		"XL",		/* 0xb3 */
		"EC Ultra", 	/* 0xb4 */
		"Extreme",	/* 0xb5 */
		"EC",		/* 0xb6 */
		"FE",		/* 0xb7 */
		"FE+",		/* 0xb8 */
		"Supreme",	/* 0xb9 */
		"UL 2",		/* 0xba */
		"Unknown",	/* 0xbb */
		"Optima",	/* 0xbc */
		"OptimaEEE",    /* 0xbd */
		"Optima 2",	/* 0xbe */
	};

	if (chipid >= CHIP_ID_YUKON_XL && chipid <= CHIP_ID_YUKON_OP_2)
		strncpy(buf, name[chipid - CHIP_ID_YUKON_XL], sz);
	else
		snprintf(buf, sz, "(chip %#x)", chipid);
	return buf;
}