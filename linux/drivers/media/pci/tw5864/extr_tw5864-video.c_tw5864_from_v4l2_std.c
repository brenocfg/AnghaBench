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
typedef  int v4l2_std_id ;
typedef  enum tw5864_vid_std { ____Placeholder_tw5864_vid_std } tw5864_vid_std ;

/* Variables and functions */
 int STD_INVALID ; 
 int STD_NTSC ; 
 int STD_NTSC443 ; 
 int STD_PAL ; 
 int STD_PAL_60 ; 
 int STD_PAL_CN ; 
 int STD_PAL_M ; 
 int STD_SECAM ; 
 int V4L2_STD_NTSC_443 ; 
 int V4L2_STD_NTSC_M ; 
 int V4L2_STD_PAL_60 ; 
 int V4L2_STD_PAL_B ; 
 int V4L2_STD_PAL_M ; 
 int V4L2_STD_PAL_Nc ; 
 int V4L2_STD_SECAM_B ; 

__attribute__((used)) static enum tw5864_vid_std tw5864_from_v4l2_std(v4l2_std_id v4l2_std)
{
	if (v4l2_std & V4L2_STD_NTSC_M)
		return STD_NTSC;
	if (v4l2_std & V4L2_STD_PAL_B)
		return STD_PAL;
	if (v4l2_std & V4L2_STD_SECAM_B)
		return STD_SECAM;
	if (v4l2_std & V4L2_STD_NTSC_443)
		return STD_NTSC443;
	if (v4l2_std & V4L2_STD_PAL_M)
		return STD_PAL_M;
	if (v4l2_std & V4L2_STD_PAL_Nc)
		return STD_PAL_CN;
	if (v4l2_std & V4L2_STD_PAL_60)
		return STD_PAL_60;

	return STD_INVALID;
}