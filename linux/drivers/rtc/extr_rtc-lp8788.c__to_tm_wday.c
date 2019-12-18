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
 int LP8788_WDAY_SET ; 
 int MAX_WDAY_BITS ; 

__attribute__((used)) static int _to_tm_wday(u8 lp8788_wday)
{
	int i;

	if (lp8788_wday == 0)
		return 0;

	/* lookup defined weekday from read register value */
	for (i = 0; i < MAX_WDAY_BITS; i++) {
		if ((lp8788_wday >> i) == LP8788_WDAY_SET)
			break;
	}

	return i + 1;
}