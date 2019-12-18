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
 unsigned int ARRAY_SIZE (int const*) ; 

__attribute__((used)) static void ov9640_res_roundup(u32 *width, u32 *height)
{
	unsigned int i;
	enum { QQCIF, QQVGA, QCIF, QVGA, CIF, VGA, SXGA };
	static const u32 res_x[] = { 88, 160, 176, 320, 352, 640, 1280 };
	static const u32 res_y[] = { 72, 120, 144, 240, 288, 480, 960 };

	for (i = 0; i < ARRAY_SIZE(res_x); i++) {
		if (res_x[i] >= *width && res_y[i] >= *height) {
			*width = res_x[i];
			*height = res_y[i];
			return;
		}
	}

	*width = res_x[SXGA];
	*height = res_y[SXGA];
}