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
struct isp_prev_device {int dummy; } ;
struct isp_device {int revision; } ;

/* Variables and functions */
#define  ISP_REVISION_15_0 130 
#define  ISP_REVISION_1_0 129 
#define  ISP_REVISION_2_0 128 
 unsigned int PREV_MAX_OUT_WIDTH_REV_1 ; 
 unsigned int PREV_MAX_OUT_WIDTH_REV_15 ; 
 unsigned int PREV_MAX_OUT_WIDTH_REV_2 ; 
 struct isp_device* to_isp_device (struct isp_prev_device*) ; 

__attribute__((used)) static unsigned int preview_max_out_width(struct isp_prev_device *prev)
{
	struct isp_device *isp = to_isp_device(prev);

	switch (isp->revision) {
	case ISP_REVISION_1_0:
		return PREV_MAX_OUT_WIDTH_REV_1;

	case ISP_REVISION_2_0:
	default:
		return PREV_MAX_OUT_WIDTH_REV_2;

	case ISP_REVISION_15_0:
		return PREV_MAX_OUT_WIDTH_REV_15;
	}
}