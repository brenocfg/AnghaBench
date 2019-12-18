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
struct ivtv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IVTV_WARN (char*) ; 
 scalar_t__ IVTV_YUV_HORIZONTAL_FILTER_OFFSET ; 
 scalar_t__ IVTV_YUV_VERTICAL_FILTER_OFFSET ; 
 int read_dec (scalar_t__) ; 

int ivtv_yuv_filter_check(struct ivtv *itv)
{
	int i, y, uv;

	for (i = 0, y = 16, uv = 4; i < 16; i++, y += 24, uv += 12) {
		if ((read_dec(IVTV_YUV_HORIZONTAL_FILTER_OFFSET + y) != i << 16) ||
		    (read_dec(IVTV_YUV_VERTICAL_FILTER_OFFSET + uv) != i << 16)) {
			IVTV_WARN ("YUV filter table not found in firmware.\n");
			return -1;
		}
	}
	return 0;
}