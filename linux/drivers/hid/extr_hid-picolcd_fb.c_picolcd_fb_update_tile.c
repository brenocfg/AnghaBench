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
typedef  int u8 ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 

__attribute__((used)) static int picolcd_fb_update_tile(u8 *vbitmap, const u8 *bitmap, int bpp,
		int chip, int tile)
{
	int i, b, changed = 0;
	u8 tdata[64];
	u8 *vdata = vbitmap + (tile * 4 + chip) * 64;

	if (bpp == 1) {
		for (b = 7; b >= 0; b--) {
			const u8 *bdata = bitmap + tile * 256 + chip * 8 + b * 32;
			for (i = 0; i < 64; i++) {
				tdata[i] <<= 1;
				tdata[i] |= (bdata[i/8] >> (i % 8)) & 0x01;
			}
		}
	} else if (bpp == 8) {
		for (b = 7; b >= 0; b--) {
			const u8 *bdata = bitmap + (tile * 256 + chip * 8 + b * 32) * 8;
			for (i = 0; i < 64; i++) {
				tdata[i] <<= 1;
				tdata[i] |= (bdata[i] & 0x80) ? 0x01 : 0x00;
			}
		}
	} else {
		/* Oops, we should never get here! */
		WARN_ON(1);
		return 0;
	}

	for (i = 0; i < 64; i++)
		if (tdata[i] != vdata[i]) {
			changed = 1;
			vdata[i] = tdata[i];
		}
	return changed;
}