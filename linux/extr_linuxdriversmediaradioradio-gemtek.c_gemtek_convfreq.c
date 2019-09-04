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

/* Variables and functions */
 unsigned long FSCALE ; 
 unsigned long IF_OFFSET ; 
 int REF_FREQ ; 

__attribute__((used)) static unsigned long gemtek_convfreq(unsigned long freq)
{
	return ((freq << FSCALE) + IF_OFFSET + REF_FREQ / 2) / REF_FREQ;
}