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
struct screen_info {int lfb_depth; int lfb_linelength; int red_size; int red_pos; int green_size; int green_pos; int blue_size; int blue_pos; int rsvd_size; int rsvd_pos; int lfb_width; } ;
struct efi_pixel_bitmask {int /*<<< orphan*/  reserved_mask; int /*<<< orphan*/  blue_mask; int /*<<< orphan*/  green_mask; int /*<<< orphan*/  red_mask; } ;

/* Variables and functions */
 int PIXEL_BGR_RESERVED_8BIT_PER_COLOR ; 
 int PIXEL_BIT_MASK ; 
 int PIXEL_RGB_RESERVED_8BIT_PER_COLOR ; 
 int /*<<< orphan*/  find_bits (int /*<<< orphan*/ ,int*,int*) ; 

__attribute__((used)) static void
setup_pixel_info(struct screen_info *si, u32 pixels_per_scan_line,
		 struct efi_pixel_bitmask pixel_info, int pixel_format)
{
	if (pixel_format == PIXEL_RGB_RESERVED_8BIT_PER_COLOR) {
		si->lfb_depth = 32;
		si->lfb_linelength = pixels_per_scan_line * 4;
		si->red_size = 8;
		si->red_pos = 0;
		si->green_size = 8;
		si->green_pos = 8;
		si->blue_size = 8;
		si->blue_pos = 16;
		si->rsvd_size = 8;
		si->rsvd_pos = 24;
	} else if (pixel_format == PIXEL_BGR_RESERVED_8BIT_PER_COLOR) {
		si->lfb_depth = 32;
		si->lfb_linelength = pixels_per_scan_line * 4;
		si->red_size = 8;
		si->red_pos = 16;
		si->green_size = 8;
		si->green_pos = 8;
		si->blue_size = 8;
		si->blue_pos = 0;
		si->rsvd_size = 8;
		si->rsvd_pos = 24;
	} else if (pixel_format == PIXEL_BIT_MASK) {
		find_bits(pixel_info.red_mask, &si->red_pos, &si->red_size);
		find_bits(pixel_info.green_mask, &si->green_pos,
			  &si->green_size);
		find_bits(pixel_info.blue_mask, &si->blue_pos, &si->blue_size);
		find_bits(pixel_info.reserved_mask, &si->rsvd_pos,
			  &si->rsvd_size);
		si->lfb_depth = si->red_size + si->green_size +
			si->blue_size + si->rsvd_size;
		si->lfb_linelength = (pixels_per_scan_line * si->lfb_depth) / 8;
	} else {
		si->lfb_depth = 4;
		si->lfb_linelength = si->lfb_width / 2;
		si->red_size = 0;
		si->red_pos = 0;
		si->green_size = 0;
		si->green_pos = 0;
		si->blue_size = 0;
		si->blue_pos = 0;
		si->rsvd_size = 0;
		si->rsvd_pos = 0;
	}
}