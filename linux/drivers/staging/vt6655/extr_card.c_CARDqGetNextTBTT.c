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
typedef  int u64 ;
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  do_div (int,int) ; 

u64 CARDqGetNextTBTT(u64 qwTSF, unsigned short wBeaconInterval)
{
	u32 beacon_int;

	beacon_int = wBeaconInterval * 1024;
	if (beacon_int) {
		do_div(qwTSF, beacon_int);
		qwTSF += 1;
		qwTSF *= beacon_int;
	}

	return qwTSF;
}