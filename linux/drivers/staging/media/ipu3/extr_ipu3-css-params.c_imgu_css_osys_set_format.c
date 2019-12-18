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
typedef  enum imgu_abi_frame_format { ____Placeholder_imgu_abi_frame_format } imgu_abi_frame_format ;

/* Variables and functions */
#define  IMGU_ABI_FRAME_FORMAT_NV12 133 
#define  IMGU_ABI_FRAME_FORMAT_NV12_TILEY 132 
#define  IMGU_ABI_FRAME_FORMAT_NV16 131 
#define  IMGU_ABI_FRAME_FORMAT_NV21 130 
#define  IMGU_ABI_FRAME_FORMAT_YUV420 129 
#define  IMGU_ABI_FRAME_FORMAT_YV12 128 
 unsigned int IMGU_ABI_OSYS_FORMAT_NV12 ; 
 unsigned int IMGU_ABI_OSYS_FORMAT_NV16 ; 
 unsigned int IMGU_ABI_OSYS_FORMAT_NV21 ; 
 unsigned int IMGU_ABI_OSYS_FORMAT_YUV420 ; 
 unsigned int IMGU_ABI_OSYS_FORMAT_YV12 ; 
 unsigned int IMGU_ABI_OSYS_TILING_NONE ; 
 unsigned int IMGU_ABI_OSYS_TILING_Y ; 

__attribute__((used)) static void imgu_css_osys_set_format(enum imgu_abi_frame_format host_format,
				     unsigned int *osys_format,
				     unsigned int *osys_tiling)
{
	*osys_format = IMGU_ABI_OSYS_FORMAT_YUV420;
	*osys_tiling = IMGU_ABI_OSYS_TILING_NONE;

	switch (host_format) {
	case IMGU_ABI_FRAME_FORMAT_YUV420:
		*osys_format = IMGU_ABI_OSYS_FORMAT_YUV420;
		break;
	case IMGU_ABI_FRAME_FORMAT_YV12:
		*osys_format = IMGU_ABI_OSYS_FORMAT_YV12;
		break;
	case IMGU_ABI_FRAME_FORMAT_NV12:
		*osys_format = IMGU_ABI_OSYS_FORMAT_NV12;
		break;
	case IMGU_ABI_FRAME_FORMAT_NV16:
		*osys_format = IMGU_ABI_OSYS_FORMAT_NV16;
		break;
	case IMGU_ABI_FRAME_FORMAT_NV21:
		*osys_format = IMGU_ABI_OSYS_FORMAT_NV21;
		break;
	case IMGU_ABI_FRAME_FORMAT_NV12_TILEY:
		*osys_format = IMGU_ABI_OSYS_FORMAT_NV12;
		*osys_tiling = IMGU_ABI_OSYS_TILING_Y;
		break;
	default:
		/* For now, assume use default values */
		break;
	}
}