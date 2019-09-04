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
typedef  scalar_t__ u32 ;
struct isp_format_info {scalar_t__ flavor; unsigned int width; } ;

/* Variables and functions */
 struct isp_format_info* omap3isp_video_format_info (scalar_t__) ; 

__attribute__((used)) static bool ccdc_is_shiftable(u32 in, u32 out, unsigned int additional_shift)
{
	const struct isp_format_info *in_info, *out_info;

	if (in == out)
		return true;

	in_info = omap3isp_video_format_info(in);
	out_info = omap3isp_video_format_info(out);

	if ((in_info->flavor == 0) || (out_info->flavor == 0))
		return false;

	if (in_info->flavor != out_info->flavor)
		return false;

	return in_info->width - out_info->width + additional_shift <= 6;
}