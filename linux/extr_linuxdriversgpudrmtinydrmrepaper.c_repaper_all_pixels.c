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
typedef  void* u8 ;
typedef  int u16 ;
struct repaper_epd {int width; } ;
typedef  enum repaper_stage { ____Placeholder_repaper_stage } repaper_stage ;

/* Variables and functions */
#define  REPAPER_COMPENSATE 131 
#define  REPAPER_INVERSE 130 
#define  REPAPER_NORMAL 129 
#define  REPAPER_WHITE 128 
 int repaper_interleave_bits (void* const) ; 

__attribute__((used)) static void repaper_all_pixels(struct repaper_epd *epd, u8 **pp,
			       const u8 *data, u8 fixed_value, const u8 *mask,
			       enum repaper_stage stage)
{
	unsigned int b;

	for (b = epd->width / 8; b > 0; b--) {
		if (data) {
			u16 pixels = repaper_interleave_bits(data[b - 1]);
			u16 pixel_mask = 0xffff;

			if (mask) {
				pixel_mask = repaper_interleave_bits(mask[b - 1]);

				pixel_mask = (pixel_mask ^ pixels) & 0x5555;
				pixel_mask |= pixel_mask << 1;
			}

			switch (stage) {
			case REPAPER_COMPENSATE: /* B -> W, W -> B (Current) */
				pixels = 0xaaaa | (pixels ^ 0x5555);
				break;
			case REPAPER_WHITE:      /* B -> N, W -> W (Current) */
				pixels = 0x5555 + (pixels ^ 0x5555);
				break;
			case REPAPER_INVERSE:    /* B -> N, W -> B (New) */
				pixels = 0x5555 | ((pixels ^ 0x5555) << 1);
				break;
			case REPAPER_NORMAL:     /* B -> B, W -> W (New) */
				pixels = 0xaaaa | pixels;
				break;
			}

			pixels = (pixels & pixel_mask) | (~pixel_mask & 0x5555);
			*(*pp)++ = pixels >> 8;
			*(*pp)++ = pixels;
		} else {
			*(*pp)++ = fixed_value;
			*(*pp)++ = fixed_value;
		}
	}
}