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
struct ivtv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IVTV_DEBUG_YUV (char*,int) ; 
 int IVTV_YUV_HORIZONTAL_FILTER_OFFSET ; 
 int IVTV_YUV_VERTICAL_FILTER_OFFSET ; 
 int /*<<< orphan*/  read_dec (int) ; 
 int /*<<< orphan*/  write_reg (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ivtv_yuv_filter(struct ivtv *itv, int h_filter, int v_filter_1, int v_filter_2)
{
	u32 i, line;

	/* If any filter is -1, then don't update it */
	if (h_filter > -1) {
		if (h_filter > 4)
			h_filter = 4;
		i = IVTV_YUV_HORIZONTAL_FILTER_OFFSET + (h_filter * 384);
		for (line = 0; line < 16; line++) {
			write_reg(read_dec(i), 0x02804);
			write_reg(read_dec(i), 0x0281c);
			i += 4;
			write_reg(read_dec(i), 0x02808);
			write_reg(read_dec(i), 0x02820);
			i += 4;
			write_reg(read_dec(i), 0x0280c);
			write_reg(read_dec(i), 0x02824);
			i += 4;
			write_reg(read_dec(i), 0x02810);
			write_reg(read_dec(i), 0x02828);
			i += 4;
			write_reg(read_dec(i), 0x02814);
			write_reg(read_dec(i), 0x0282c);
			i += 8;
			write_reg(0, 0x02818);
			write_reg(0, 0x02830);
		}
		IVTV_DEBUG_YUV("h_filter -> %d\n", h_filter);
	}

	if (v_filter_1 > -1) {
		if (v_filter_1 > 4)
			v_filter_1 = 4;
		i = IVTV_YUV_VERTICAL_FILTER_OFFSET + (v_filter_1 * 192);
		for (line = 0; line < 16; line++) {
			write_reg(read_dec(i), 0x02900);
			i += 4;
			write_reg(read_dec(i), 0x02904);
			i += 8;
			write_reg(0, 0x02908);
		}
		IVTV_DEBUG_YUV("v_filter_1 -> %d\n", v_filter_1);
	}

	if (v_filter_2 > -1) {
		if (v_filter_2 > 4)
			v_filter_2 = 4;
		i = IVTV_YUV_VERTICAL_FILTER_OFFSET + (v_filter_2 * 192);
		for (line = 0; line < 16; line++) {
			write_reg(read_dec(i), 0x0290c);
			i += 4;
			write_reg(read_dec(i), 0x02910);
			i += 8;
			write_reg(0, 0x02914);
		}
		IVTV_DEBUG_YUV("v_filter_2 -> %d\n", v_filter_2);
	}
}