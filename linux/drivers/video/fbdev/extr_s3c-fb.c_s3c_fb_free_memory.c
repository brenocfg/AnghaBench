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
struct s3c_fb_win {struct fb_info* fbinfo; } ;
struct s3c_fb {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  smem_start; int /*<<< orphan*/  smem_len; } ;
struct fb_info {TYPE_1__ fix; scalar_t__ screen_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_ALIGN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_wc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void s3c_fb_free_memory(struct s3c_fb *sfb, struct s3c_fb_win *win)
{
	struct fb_info *fbi = win->fbinfo;

	if (fbi->screen_buffer)
		dma_free_wc(sfb->dev, PAGE_ALIGN(fbi->fix.smem_len),
			    fbi->screen_buffer, fbi->fix.smem_start);
}