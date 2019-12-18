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
struct repaper_epd {int width; } ;
typedef  enum repaper_stage { ____Placeholder_repaper_stage } repaper_stage ;

/* Variables and functions */
#define  REPAPER_COMPENSATE 131 
#define  REPAPER_INVERSE 130 
#define  REPAPER_NORMAL 129 
#define  REPAPER_WHITE 128 

__attribute__((used)) static void repaper_odd_pixels(struct repaper_epd *epd, u8 **pp,
			       const u8 *data, u8 fixed_value, const u8 *mask,
			       enum repaper_stage stage)
{
	unsigned int b;

	for (b = epd->width / 8; b > 0; b--) {
		if (data) {
			u8 pixels = data[b - 1] & 0x55;
			u8 pixel_mask = 0xff;

			if (mask) {
				pixel_mask = (mask[b - 1] ^ pixels) & 0x55;
				pixel_mask |= pixel_mask << 1;
			}

			switch (stage) {
			case REPAPER_COMPENSATE: /* B -> W, W -> B (Current) */
				pixels = 0xaa | (pixels ^ 0x55);
				break;
			case REPAPER_WHITE:      /* B -> N, W -> W (Current) */
				pixels = 0x55 + (pixels ^ 0x55);
				break;
			case REPAPER_INVERSE:    /* B -> N, W -> B (New) */
				pixels = 0x55 | ((pixels ^ 0x55) << 1);
				break;
			case REPAPER_NORMAL:     /* B -> B, W -> W (New) */
				pixels = 0xaa | pixels;
				break;
			}

			pixels = (pixels & pixel_mask) | (~pixel_mask & 0x55);
			*(*pp)++ = pixels;
		} else {
			*(*pp)++ = fixed_value;
		}
	}
}