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
struct v4l2_format_info {unsigned int* block_w; } ;

/* Variables and functions */

__attribute__((used)) static inline unsigned int v4l2_format_block_width(const struct v4l2_format_info *info, int plane)
{
	if (!info->block_w[plane])
		return 1;
	return info->block_w[plane];
}