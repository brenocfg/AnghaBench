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
typedef  unsigned int uint64_t ;

/* Variables and functions */
 unsigned int DIV_ROUND_UP_ULL (unsigned int,int) ; 

__attribute__((used)) static unsigned int intel_wm_method1(unsigned int pixel_rate,
				     unsigned int cpp,
				     unsigned int latency)
{
	uint64_t ret;

	ret = (uint64_t) pixel_rate * cpp * latency;
	ret = DIV_ROUND_UP_ULL(ret, 10000);

	return ret;
}