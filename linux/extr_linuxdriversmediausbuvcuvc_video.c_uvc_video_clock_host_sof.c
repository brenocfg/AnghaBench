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
typedef  int u16 ;
struct uvc_clock_sample {int host_sof; int dev_sof; } ;
typedef  int s8 ;

/* Variables and functions */

__attribute__((used)) static u16 uvc_video_clock_host_sof(const struct uvc_clock_sample *sample)
{
	/* The delta value can be negative. */
	s8 delta_sof;

	delta_sof = (sample->host_sof - sample->dev_sof) & 255;

	return (sample->dev_sof + delta_sof) & 2047;
}