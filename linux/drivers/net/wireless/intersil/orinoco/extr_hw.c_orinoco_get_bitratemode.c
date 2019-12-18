#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int bitrate; int automatic; } ;

/* Variables and functions */
 int BITRATE_TABLE_SIZE ; 
 TYPE_1__* bitrate_table ; 

int orinoco_get_bitratemode(int bitrate, int automatic)
{
	int ratemode = -1;
	int i;

	if ((bitrate != 10) && (bitrate != 20) &&
	    (bitrate != 55) && (bitrate != 110))
		return ratemode;

	for (i = 0; i < BITRATE_TABLE_SIZE; i++) {
		if ((bitrate_table[i].bitrate == bitrate) &&
		    (bitrate_table[i].automatic == automatic)) {
			ratemode = i;
			break;
		}
	}
	return ratemode;
}