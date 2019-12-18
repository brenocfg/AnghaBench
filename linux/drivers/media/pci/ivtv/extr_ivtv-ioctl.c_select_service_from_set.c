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
typedef  int u16 ;

/* Variables and functions */
 int BIT (int) ; 
 int V4L2_SLICED_CAPTION_525 ; 
 int V4L2_SLICED_VBI_525 ; 
 int V4L2_SLICED_VBI_625 ; 
 int V4L2_SLICED_VPS ; 
 int V4L2_SLICED_WSS_625 ; 
 int /*<<< orphan*/  valid_service_line (int,int,int) ; 

__attribute__((used)) static u16 select_service_from_set(int field, int line, u16 set, int is_pal)
{
	u16 valid_set = (is_pal ? V4L2_SLICED_VBI_625 : V4L2_SLICED_VBI_525);
	int i;

	set = set & valid_set;
	if (set == 0 || !valid_service_line(field, line, is_pal)) {
		return 0;
	}
	if (!is_pal) {
		if (line == 21 && (set & V4L2_SLICED_CAPTION_525))
			return V4L2_SLICED_CAPTION_525;
	}
	else {
		if (line == 16 && field == 0 && (set & V4L2_SLICED_VPS))
			return V4L2_SLICED_VPS;
		if (line == 23 && field == 0 && (set & V4L2_SLICED_WSS_625))
			return V4L2_SLICED_WSS_625;
		if (line == 23)
			return 0;
	}
	for (i = 0; i < 32; i++) {
		if (BIT(i) & set)
			return BIT(i);
	}
	return 0;
}