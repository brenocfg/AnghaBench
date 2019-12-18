#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct v4l2_rect {int width; int height; int left; int top; } ;
struct v4l2_pix_format {int width; int height; } ;
struct TYPE_2__ {int width; int height; } ;
struct v4l2_framebuffer {TYPE_1__ fmt; } ;

/* Variables and functions */

void omap_vout_default_crop(struct v4l2_pix_format *pix,
		  struct v4l2_framebuffer *fbuf, struct v4l2_rect *crop)
{
	crop->width = (pix->width < fbuf->fmt.width) ?
		pix->width : fbuf->fmt.width;
	crop->height = (pix->height < fbuf->fmt.height) ?
		pix->height : fbuf->fmt.height;
	crop->width &= ~1;
	crop->height &= ~1;
	crop->left = ((pix->width - crop->width) >> 1) & ~1;
	crop->top = ((pix->height - crop->height) >> 1) & ~1;
}