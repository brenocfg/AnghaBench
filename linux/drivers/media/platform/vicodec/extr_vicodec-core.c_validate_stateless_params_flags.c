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
struct v4l2_fwht_pixfmt_info {int dummy; } ;
struct v4l2_ctrl_fwht_params {int flags; int version; } ;

/* Variables and functions */
 int FWHT_FL_CHROMA_FULL_HEIGHT ; 
 int FWHT_FL_CHROMA_FULL_WIDTH ; 
 int FWHT_FL_COMPONENTS_NUM_MSK ; 
 int FWHT_FL_COMPONENTS_NUM_OFFSET ; 
 unsigned int FWHT_FL_PIXENC_MSK ; 
 scalar_t__ v4l2_fwht_validate_fmt (struct v4l2_fwht_pixfmt_info const*,unsigned int,unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static bool validate_stateless_params_flags(const struct v4l2_ctrl_fwht_params *params,
					    const struct v4l2_fwht_pixfmt_info *cur_info)
{
	unsigned int width_div =
		(params->flags & FWHT_FL_CHROMA_FULL_WIDTH) ? 1 : 2;
	unsigned int height_div =
		(params->flags & FWHT_FL_CHROMA_FULL_HEIGHT) ? 1 : 2;
	unsigned int components_num = 3;
	unsigned int pixenc = 0;

	if (params->version < 3)
		return false;

	components_num = 1 + ((params->flags & FWHT_FL_COMPONENTS_NUM_MSK) >>
			      FWHT_FL_COMPONENTS_NUM_OFFSET);
	pixenc = (params->flags & FWHT_FL_PIXENC_MSK);
	if (v4l2_fwht_validate_fmt(cur_info, width_div, height_div,
				    components_num, pixenc))
		return true;
	return false;
}