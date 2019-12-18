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
#define  DRM_FORMAT_YVU411 131 
#define  DRM_FORMAT_YVU420 130 
#define  DRM_FORMAT_YVU422 129 
#define  DRM_FORMAT_YVU444 128 

__attribute__((used)) static bool sun4i_frontend_format_chroma_requires_swap(uint32_t fmt)
{
	switch (fmt) {
	case DRM_FORMAT_YVU411:
	case DRM_FORMAT_YVU420:
	case DRM_FORMAT_YVU422:
	case DRM_FORMAT_YVU444:
		return true;

	default:
		return false;
	}
}