#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct picolcd_fb_data {int bpp; int* bitmap; } ;
struct TYPE_4__ {int bits_per_pixel; } ;
struct TYPE_3__ {int line_length; int /*<<< orphan*/  visual; } ;
struct fb_info {TYPE_2__ var; TYPE_1__ fix; struct picolcd_fb_data* par; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FB_VISUAL_DIRECTCOLOR ; 
 int /*<<< orphan*/  FB_VISUAL_MONO01 ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PICOLCDFB_SIZE ; 
 int PICOLCDFB_WIDTH ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 

__attribute__((used)) static int picolcd_set_par(struct fb_info *info)
{
	struct picolcd_fb_data *fbdata = info->par;
	u8 *tmp_fb, *o_fb;
	if (info->var.bits_per_pixel == fbdata->bpp)
		return 0;
	/* switch between 1/8 bit depths */
	if (info->var.bits_per_pixel != 1 && info->var.bits_per_pixel != 8)
		return -EINVAL;

	o_fb   = fbdata->bitmap;
	tmp_fb = kmalloc_array(PICOLCDFB_SIZE, info->var.bits_per_pixel,
			       GFP_KERNEL);
	if (!tmp_fb)
		return -ENOMEM;

	/* translate FB content to new bits-per-pixel */
	if (info->var.bits_per_pixel == 1) {
		int i, b;
		for (i = 0; i < PICOLCDFB_SIZE; i++) {
			u8 p = 0;
			for (b = 0; b < 8; b++) {
				p <<= 1;
				p |= o_fb[i*8+b] ? 0x01 : 0x00;
			}
			tmp_fb[i] = p;
		}
		memcpy(o_fb, tmp_fb, PICOLCDFB_SIZE);
		info->fix.visual = FB_VISUAL_MONO01;
		info->fix.line_length = PICOLCDFB_WIDTH / 8;
	} else {
		int i;
		memcpy(tmp_fb, o_fb, PICOLCDFB_SIZE);
		for (i = 0; i < PICOLCDFB_SIZE * 8; i++)
			o_fb[i] = tmp_fb[i/8] & (0x01 << (7 - i % 8)) ? 0xff : 0x00;
		info->fix.visual = FB_VISUAL_DIRECTCOLOR;
		info->fix.line_length = PICOLCDFB_WIDTH;
	}

	kfree(tmp_fb);
	fbdata->bpp = info->var.bits_per_pixel;
	return 0;
}