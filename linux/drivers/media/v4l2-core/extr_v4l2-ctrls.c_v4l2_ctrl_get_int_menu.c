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
typedef  int s64 ;

/* Variables and functions */
#define  V4L2_CID_MPEG_VIDEO_VPX_NUM_PARTITIONS 129 
#define  V4L2_CID_MPEG_VIDEO_VPX_NUM_REF_FRAMES 128 
 int const* __v4l2_qmenu_int_len (int const*,int*) ; 

const s64 *v4l2_ctrl_get_int_menu(u32 id, u32 *len)
{
	static const s64 qmenu_int_vpx_num_partitions[] = {
		1, 2, 4, 8,
	};

	static const s64 qmenu_int_vpx_num_ref_frames[] = {
		1, 2, 3,
	};

	switch (id) {
	case V4L2_CID_MPEG_VIDEO_VPX_NUM_PARTITIONS:
		return __v4l2_qmenu_int_len(qmenu_int_vpx_num_partitions, len);
	case V4L2_CID_MPEG_VIDEO_VPX_NUM_REF_FRAMES:
		return __v4l2_qmenu_int_len(qmenu_int_vpx_num_ref_frames, len);
	default:
		*len = 0;
		return NULL;
	}
}