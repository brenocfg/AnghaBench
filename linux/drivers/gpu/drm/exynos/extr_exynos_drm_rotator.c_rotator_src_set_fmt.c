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
struct rot_context {int dummy; } ;

/* Variables and functions */
#define  DRM_FORMAT_NV12 129 
#define  DRM_FORMAT_XRGB8888 128 
 int /*<<< orphan*/  ROT_CONTROL ; 
 int ROT_CONTROL_FMT_MASK ; 
 int ROT_CONTROL_FMT_RGB888 ; 
 int ROT_CONTROL_FMT_YCBCR420_2P ; 
 int rot_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rot_write (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rotator_src_set_fmt(struct rot_context *rot, u32 fmt)
{
	u32 val;

	val = rot_read(ROT_CONTROL);
	val &= ~ROT_CONTROL_FMT_MASK;

	switch (fmt) {
	case DRM_FORMAT_NV12:
		val |= ROT_CONTROL_FMT_YCBCR420_2P;
		break;
	case DRM_FORMAT_XRGB8888:
		val |= ROT_CONTROL_FMT_RGB888;
		break;
	}

	rot_write(val, ROT_CONTROL);
}