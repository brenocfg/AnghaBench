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
 int ALIGN (int,int) ; 
 int DIV_ROUND_UP (int,int) ; 
 int SZ_16K ; 
 int SZ_4K ; 
 int max (int,int) ; 

__attribute__((used)) static u32 get_framesize_raw_nv12_ubwc(u32 width, u32 height)
{
	u32 y_meta_stride, y_meta_plane;
	u32 y_stride, y_plane;
	u32 uv_meta_stride, uv_meta_plane;
	u32 uv_stride, uv_plane;
	u32 extradata = SZ_16K;

	y_meta_stride = ALIGN(DIV_ROUND_UP(width, 32), 64);
	y_meta_plane = y_meta_stride * ALIGN(DIV_ROUND_UP(height, 8), 16);
	y_meta_plane = ALIGN(y_meta_plane, SZ_4K);

	y_stride = ALIGN(width, 128);
	y_plane = ALIGN(y_stride * ALIGN(height, 32), SZ_4K);

	uv_meta_stride = ALIGN(DIV_ROUND_UP(width / 2, 16), 64);
	uv_meta_plane = uv_meta_stride * ALIGN(DIV_ROUND_UP(height / 2, 8), 16);
	uv_meta_plane = ALIGN(uv_meta_plane, SZ_4K);

	uv_stride = ALIGN(width, 128);
	uv_plane = ALIGN(uv_stride * ALIGN(height / 2, 32), SZ_4K);

	return ALIGN(y_meta_plane + y_plane + uv_meta_plane + uv_plane +
		     max(extradata, y_stride * 48), SZ_4K);
}