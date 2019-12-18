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
#define  DRM_FORMAT_X0L2 129 
#define  DRM_FORMAT_YUV420_10BIT 128 
 int EINVAL ; 
 int malidpx50_get_bytes_per_column (int) ; 

__attribute__((used)) static int malidp550_rotmem_required(struct malidp_hw_device *hwdev, u16 w,
				     u16 h, u32 fmt, bool has_modifier)
{
	int bytes_per_column = 0;

	switch (fmt) {
	/* 8 lines at 15 bits per pixel */
	case DRM_FORMAT_YUV420_10BIT:
		bytes_per_column = 15;
		break;
	/* Uncompressed YUV 420 10 bit single plane cannot be rotated */
	case DRM_FORMAT_X0L2:
		if (has_modifier)
			bytes_per_column = 8;
		else
			return -EINVAL;
		break;
	default:
		bytes_per_column = malidpx50_get_bytes_per_column(fmt);
	}

	if (bytes_per_column == -EINVAL)
		return bytes_per_column;

	return w * bytes_per_column;
}