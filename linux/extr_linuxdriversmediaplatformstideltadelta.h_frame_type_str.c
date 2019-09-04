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
 int V4L2_BUF_FLAG_BFRAME ; 
 int V4L2_BUF_FLAG_KEYFRAME ; 
 int V4L2_BUF_FLAG_LAST ; 
 int V4L2_BUF_FLAG_PFRAME ; 

__attribute__((used)) static inline char *frame_type_str(u32 flags)
{
	if (flags & V4L2_BUF_FLAG_KEYFRAME)
		return "I";
	if (flags & V4L2_BUF_FLAG_PFRAME)
		return "P";
	if (flags & V4L2_BUF_FLAG_BFRAME)
		return "B";
	if (flags & V4L2_BUF_FLAG_LAST)
		return "EOS";
	return "?";
}