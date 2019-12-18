#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int member_0; int member_1; int member_2; } ;
struct TYPE_6__ {int member_0; int member_1; int member_2; } ;
struct TYPE_8__ {int member_0; int member_1; int member_2; } ;
struct TYPE_9__ {TYPE_2__ member_2; TYPE_1__ member_1; TYPE_3__ member_0; } ;
typedef  TYPE_4__ u32 ;
struct scaler_context {int dummy; } ;
struct drm_format_info {int format; } ;

/* Variables and functions */
#define  DRM_FORMAT_ARGB1555 136 
#define  DRM_FORMAT_ARGB4444 135 
#define  DRM_FORMAT_ARGB8888 134 
#define  DRM_FORMAT_RGB565 133 
#define  DRM_FORMAT_RGBA8888 132 
#define  DRM_FORMAT_RGBX8888 131 
#define  DRM_FORMAT_XRGB1555 130 
#define  DRM_FORMAT_XRGB4444 129 
#define  DRM_FORMAT_XRGB8888 128 
 int /*<<< orphan*/  SCALER_CSC_COEF (int,int) ; 
 int /*<<< orphan*/  scaler_write (TYPE_4__ const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void scaler_set_csc(struct scaler_context *scaler,
	const struct drm_format_info *fmt)
{
	static const u32 csc_mtx[2][3][3] = {
		{ /* YCbCr to RGB */
			{0x254, 0x000, 0x331},
			{0x254, 0xf38, 0xe60},
			{0x254, 0x409, 0x000},
		},
		{ /* RGB to YCbCr */
			{0x084, 0x102, 0x032},
			{0xfb4, 0xf6b, 0x0e1},
			{0x0e1, 0xf44, 0xfdc},
		},
	};
	int i, j, dir;

	switch (fmt->format) {
	case DRM_FORMAT_RGB565:
	case DRM_FORMAT_XRGB1555:
	case DRM_FORMAT_ARGB1555:
	case DRM_FORMAT_XRGB4444:
	case DRM_FORMAT_ARGB4444:
	case DRM_FORMAT_XRGB8888:
	case DRM_FORMAT_ARGB8888:
	case DRM_FORMAT_RGBX8888:
	case DRM_FORMAT_RGBA8888:
		dir = 1;
		break;
	default:
		dir = 0;
	}

	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
			scaler_write(csc_mtx[dir][i][j], SCALER_CSC_COEF(j, i));
}