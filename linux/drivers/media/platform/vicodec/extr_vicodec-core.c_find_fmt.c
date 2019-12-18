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
typedef  int /*<<< orphan*/  u32 ;
struct v4l2_fwht_pixfmt_info {int dummy; } ;

/* Variables and functions */
 struct v4l2_fwht_pixfmt_info* v4l2_fwht_find_pixfmt (int /*<<< orphan*/ ) ; 
 struct v4l2_fwht_pixfmt_info* v4l2_fwht_get_pixfmt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const struct v4l2_fwht_pixfmt_info *find_fmt(u32 fmt)
{
	const struct v4l2_fwht_pixfmt_info *info =
		v4l2_fwht_find_pixfmt(fmt);

	if (!info)
		info = v4l2_fwht_get_pixfmt(0);
	return info;
}