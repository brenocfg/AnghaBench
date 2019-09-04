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
typedef  int /*<<< orphan*/  v4l2_std_id ;
typedef  enum tw5864_vid_std { ____Placeholder_tw5864_vid_std } tw5864_vid_std ;

/* Variables and functions */
#define  STD_INVALID 135 
#define  STD_NTSC 134 
#define  STD_NTSC443 133 
#define  STD_PAL 132 
#define  STD_PAL_60 131 
#define  STD_PAL_CN 130 
#define  STD_PAL_M 129 
#define  STD_SECAM 128 
 int /*<<< orphan*/  V4L2_STD_NTSC_443 ; 
 int /*<<< orphan*/  V4L2_STD_NTSC_M ; 
 int /*<<< orphan*/  V4L2_STD_PAL_60 ; 
 int /*<<< orphan*/  V4L2_STD_PAL_B ; 
 int /*<<< orphan*/  V4L2_STD_PAL_M ; 
 int /*<<< orphan*/  V4L2_STD_PAL_Nc ; 
 int /*<<< orphan*/  V4L2_STD_SECAM_B ; 
 int /*<<< orphan*/  V4L2_STD_UNKNOWN ; 

__attribute__((used)) static v4l2_std_id tw5864_get_v4l2_std(enum tw5864_vid_std std)
{
	switch (std) {
	case STD_NTSC:    return V4L2_STD_NTSC_M;
	case STD_PAL:     return V4L2_STD_PAL_B;
	case STD_SECAM:   return V4L2_STD_SECAM_B;
	case STD_NTSC443: return V4L2_STD_NTSC_443;
	case STD_PAL_M:   return V4L2_STD_PAL_M;
	case STD_PAL_CN:  return V4L2_STD_PAL_Nc;
	case STD_PAL_60:  return V4L2_STD_PAL_60;
	case STD_INVALID: return V4L2_STD_UNKNOWN;
	}
	return 0;
}