#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_4__ {int bitrate; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int* mcs ; 
 TYPE_1__* rsi_mcsrates ; 
 TYPE_1__* rsi_rates ; 

__attribute__((used)) static bool rsi_map_rates(u16 rate, int *offset)
{
	int kk;
	for (kk = 0; kk < ARRAY_SIZE(rsi_mcsrates); kk++) {
		if (rate == mcs[kk]) {
			*offset = kk;
			return false;
		}
	}

	for (kk = 0; kk < ARRAY_SIZE(rsi_rates); kk++) {
		if (rate == rsi_rates[kk].bitrate / 5) {
			*offset = kk;
			break;
		}
	}
	return true;
}