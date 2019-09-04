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
typedef  enum pixel_format { ____Placeholder_pixel_format } pixel_format ;

/* Variables and functions */
 int PIXEL_FORMAT_420BPP10 ; 
 int PIXEL_FORMAT_420BPP8 ; 

__attribute__((used)) static bool dpp1_dscl_is_420_format(enum pixel_format format)
{
	if (format == PIXEL_FORMAT_420BPP8 ||
			format == PIXEL_FORMAT_420BPP10)
		return true;
	else
		return false;
}