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
struct vc_data {unsigned short vc_video_erase_char; int /*<<< orphan*/  vc_cols; int /*<<< orphan*/  vc_rows; scalar_t__ vc_hi_font_mask; } ;
struct fb_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fbcon_clear (struct vc_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fbcon_generic_blank(struct vc_data *vc, struct fb_info *info,
				int blank)
{
	if (blank) {
		unsigned short charmask = vc->vc_hi_font_mask ?
			0x1ff : 0xff;
		unsigned short oldc;

		oldc = vc->vc_video_erase_char;
		vc->vc_video_erase_char &= charmask;
		fbcon_clear(vc, 0, 0, vc->vc_rows, vc->vc_cols);
		vc->vc_video_erase_char = oldc;
	}
}