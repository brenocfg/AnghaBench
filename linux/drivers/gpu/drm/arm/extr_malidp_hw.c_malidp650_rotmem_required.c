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
typedef  int u16 ;
struct malidp_hw_device {int dummy; } ;

/* Variables and functions */
#define  DRM_FORMAT_X0L2 128 
 int EINVAL ; 
 int malidpx50_get_bytes_per_column (int) ; 

__attribute__((used)) static int malidp650_rotmem_required(struct malidp_hw_device *hwdev, u16 w,
				     u16 h, u32 fmt, bool has_modifier)
{
	int bytes_per_column = 0;

	switch (fmt) {
	/* 16 lines at 2 bytes per pixel */
	case DRM_FORMAT_X0L2:
		bytes_per_column = 32;
		break;
	default:
		bytes_per_column = malidpx50_get_bytes_per_column(fmt);
	}

	if (bytes_per_column == -EINVAL)
		return bytes_per_column;

	return w * bytes_per_column;
}