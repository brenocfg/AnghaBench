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

/* Variables and functions */
 int ADV748X_AFE_STD_NTSC_443 ; 
 int ADV748X_AFE_STD_NTSC_M ; 
 int ADV748X_AFE_STD_PAL60 ; 
 int ADV748X_AFE_STD_PAL_BG ; 
 int ADV748X_AFE_STD_PAL_COMB_N ; 
 int ADV748X_AFE_STD_PAL_M ; 
 int ADV748X_AFE_STD_PAL_N ; 
 int ADV748X_AFE_STD_PAL_SECAM ; 
 int EINVAL ; 
 int V4L2_STD_NTSC ; 
 int V4L2_STD_NTSC_443 ; 
 int V4L2_STD_PAL ; 
 int V4L2_STD_PAL_60 ; 
 int V4L2_STD_PAL_M ; 
 int V4L2_STD_PAL_N ; 
 int V4L2_STD_PAL_Nc ; 
 int V4L2_STD_SECAM ; 

__attribute__((used)) static int adv748x_afe_std(v4l2_std_id std)
{
	if (std == V4L2_STD_PAL_60)
		return ADV748X_AFE_STD_PAL60;
	if (std == V4L2_STD_NTSC_443)
		return ADV748X_AFE_STD_NTSC_443;
	if (std == V4L2_STD_PAL_N)
		return ADV748X_AFE_STD_PAL_N;
	if (std == V4L2_STD_PAL_M)
		return ADV748X_AFE_STD_PAL_M;
	if (std == V4L2_STD_PAL_Nc)
		return ADV748X_AFE_STD_PAL_COMB_N;
	if (std & V4L2_STD_NTSC)
		return ADV748X_AFE_STD_NTSC_M;
	if (std & V4L2_STD_PAL)
		return ADV748X_AFE_STD_PAL_BG;
	if (std & V4L2_STD_SECAM)
		return ADV748X_AFE_STD_PAL_SECAM;

	return -EINVAL;
}