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
typedef  int u32 ;

/* Variables and functions */
 int MAX2175_BAND_AM ; 
 int MAX2175_BAND_FM ; 
 int MAX2175_BAND_VHF ; 

__attribute__((used)) static int max2175_band_from_freq(u32 freq)
{
	if (freq >= 144000 && freq <= 26100000)
		return MAX2175_BAND_AM;
	else if (freq >= 65000000 && freq <= 108000000)
		return MAX2175_BAND_FM;

	return MAX2175_BAND_VHF;
}