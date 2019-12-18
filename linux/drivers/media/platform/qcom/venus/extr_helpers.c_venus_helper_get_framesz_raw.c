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

/* Variables and functions */
#define  HFI_COLOR_FORMAT_NV12 130 
#define  HFI_COLOR_FORMAT_NV12_UBWC 129 
#define  HFI_COLOR_FORMAT_NV21 128 
 int get_framesize_raw_nv12 (int,int) ; 
 int get_framesize_raw_nv12_ubwc (int,int) ; 

u32 venus_helper_get_framesz_raw(u32 hfi_fmt, u32 width, u32 height)
{
	switch (hfi_fmt) {
	case HFI_COLOR_FORMAT_NV12:
	case HFI_COLOR_FORMAT_NV21:
		return get_framesize_raw_nv12(width, height);
	case HFI_COLOR_FORMAT_NV12_UBWC:
		return get_framesize_raw_nv12_ubwc(width, height);
	default:
		return 0;
	}
}