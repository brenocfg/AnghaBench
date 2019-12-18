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
struct intelfb_info {int fb_start; int /*<<< orphan*/  ring_space; int /*<<< orphan*/  ring_tail; int /*<<< orphan*/  ring_head; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADVANCE_RING () ; 
 int COLOR_BLT_CMD ; 
 int COLOR_DEPTH_16 ; 
 int COLOR_DEPTH_32 ; 
 int COLOR_DEPTH_8 ; 
 int /*<<< orphan*/  DBG_MSG (char*,int,int,int,...) ; 
 int HEIGHT_SHIFT ; 
 int MI_NOOP ; 
 int /*<<< orphan*/  OUT_RING (int) ; 
 int ROP_SHIFT ; 
 int /*<<< orphan*/  START_RING (int) ; 
 int WIDTH_SHIFT ; 
 int WRITE_ALPHA ; 
 int WRITE_RGB ; 

void intelfbhw_do_fillrect(struct intelfb_info *dinfo, u32 x, u32 y, u32 w,
			   u32 h, u32 color, u32 pitch, u32 bpp, u32 rop)
{
	u32 br00, br09, br13, br14, br16;

#if VERBOSE > 0
	DBG_MSG("intelfbhw_do_fillrect: (%d,%d) %dx%d, c 0x%06x, p %d bpp %d, "
		"rop 0x%02x\n", x, y, w, h, color, pitch, bpp, rop);
#endif

	br00 = COLOR_BLT_CMD;
	br09 = dinfo->fb_start + (y * pitch + x * (bpp / 8));
	br13 = (rop << ROP_SHIFT) | pitch;
	br14 = (h << HEIGHT_SHIFT) | ((w * (bpp / 8)) << WIDTH_SHIFT);
	br16 = color;

	switch (bpp) {
	case 8:
		br13 |= COLOR_DEPTH_8;
		break;
	case 16:
		br13 |= COLOR_DEPTH_16;
		break;
	case 32:
		br13 |= COLOR_DEPTH_32;
		br00 |= WRITE_ALPHA | WRITE_RGB;
		break;
	}

	START_RING(6);
	OUT_RING(br00);
	OUT_RING(br13);
	OUT_RING(br14);
	OUT_RING(br09);
	OUT_RING(br16);
	OUT_RING(MI_NOOP);
	ADVANCE_RING();

#if VERBOSE > 0
	DBG_MSG("ring = 0x%08x, 0x%08x (%d)\n", dinfo->ring_head,
		dinfo->ring_tail, dinfo->ring_space);
#endif
}