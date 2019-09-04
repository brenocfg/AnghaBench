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
 scalar_t__ WARN_ON_ONCE (int) ; 

__attribute__((used)) static unsigned int intel_wm_method2(unsigned int pixel_rate,
				     unsigned int htotal,
				     unsigned int width,
				     unsigned int cpp,
				     unsigned int latency)
{
	unsigned int ret;

	/*
	 * FIXME remove once all users are computing
	 * watermarks in the correct place.
	 */
	if (WARN_ON_ONCE(htotal == 0))
		htotal = 1;

	ret = (latency * pixel_rate) / (htotal * 10000);
	ret = (ret + 1) * width * cpp;

	return ret;
}