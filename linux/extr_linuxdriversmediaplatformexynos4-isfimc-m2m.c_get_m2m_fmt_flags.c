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
 unsigned int FMT_FLAGS_M2M_IN ; 
 unsigned int FMT_FLAGS_M2M_OUT ; 
 unsigned int V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE ; 

__attribute__((used)) static unsigned int get_m2m_fmt_flags(unsigned int stream_type)
{
	if (stream_type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE)
		return FMT_FLAGS_M2M_IN;
	else
		return FMT_FLAGS_M2M_OUT;
}