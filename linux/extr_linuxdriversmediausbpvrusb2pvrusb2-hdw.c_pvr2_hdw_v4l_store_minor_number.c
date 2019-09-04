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
struct pvr2_hdw {int v4l_minor_number_video; int v4l_minor_number_vbi; int v4l_minor_number_radio; } ;
typedef  enum pvr2_v4l_type { ____Placeholder_pvr2_v4l_type } pvr2_v4l_type ;

/* Variables and functions */
#define  pvr2_v4l_type_radio 130 
#define  pvr2_v4l_type_vbi 129 
#define  pvr2_v4l_type_video 128 

void pvr2_hdw_v4l_store_minor_number(struct pvr2_hdw *hdw,
				     enum pvr2_v4l_type index,int v)
{
	switch (index) {
	case pvr2_v4l_type_video: hdw->v4l_minor_number_video = v;break;
	case pvr2_v4l_type_vbi: hdw->v4l_minor_number_vbi = v;break;
	case pvr2_v4l_type_radio: hdw->v4l_minor_number_radio = v;break;
	default: break;
	}
}