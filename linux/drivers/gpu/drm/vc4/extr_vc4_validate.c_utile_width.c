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
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 

__attribute__((used)) static uint32_t
utile_width(int cpp)
{
	switch (cpp) {
	case 1:
	case 2:
		return 8;
	case 4:
		return 4;
	case 8:
		return 2;
	default:
		DRM_ERROR("unknown cpp: %d\n", cpp);
		return 1;
	}
}