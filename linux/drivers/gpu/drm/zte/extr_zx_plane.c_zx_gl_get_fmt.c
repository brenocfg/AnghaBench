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
typedef  int uint32_t ;

/* Variables and functions */
#define  DRM_FORMAT_ARGB1555 133 
#define  DRM_FORMAT_ARGB4444 132 
#define  DRM_FORMAT_ARGB8888 131 
#define  DRM_FORMAT_RGB565 130 
#define  DRM_FORMAT_RGB888 129 
#define  DRM_FORMAT_XRGB8888 128 
 int EINVAL ; 
 int GL_FMT_ARGB1555 ; 
 int GL_FMT_ARGB4444 ; 
 int GL_FMT_ARGB8888 ; 
 int GL_FMT_RGB565 ; 
 int GL_FMT_RGB888 ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,int) ; 

__attribute__((used)) static int zx_gl_get_fmt(uint32_t format)
{
	switch (format) {
	case DRM_FORMAT_ARGB8888:
	case DRM_FORMAT_XRGB8888:
		return GL_FMT_ARGB8888;
	case DRM_FORMAT_RGB888:
		return GL_FMT_RGB888;
	case DRM_FORMAT_RGB565:
		return GL_FMT_RGB565;
	case DRM_FORMAT_ARGB1555:
		return GL_FMT_ARGB1555;
	case DRM_FORMAT_ARGB4444:
		return GL_FMT_ARGB4444;
	default:
		WARN_ONCE(1, "invalid pixel format %d\n", format);
		return -EINVAL;
	}
}