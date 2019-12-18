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
struct vc_data {size_t vc_num; } ;
struct fbcon_display {scalar_t__ yscroll; scalar_t__ vrows; } ;
struct fb_info {int dummy; } ;

/* Variables and functions */
 size_t* con2fb_map ; 
 struct fbcon_display* fb_display ; 
 int /*<<< orphan*/  fbcon_bmove_rec (struct vc_data*,struct fbcon_display*,int,int,int,int,int,int,scalar_t__) ; 
 scalar_t__ fbcon_is_inactive (struct vc_data*,struct fb_info*) ; 
 struct fb_info** registered_fb ; 

__attribute__((used)) static void fbcon_bmove(struct vc_data *vc, int sy, int sx, int dy, int dx,
			int height, int width)
{
	struct fb_info *info = registered_fb[con2fb_map[vc->vc_num]];
	struct fbcon_display *p = &fb_display[vc->vc_num];
	
	if (fbcon_is_inactive(vc, info))
		return;

	if (!width || !height)
		return;

	/*  Split blits that cross physical y_wrap case.
	 *  Pathological case involves 4 blits, better to use recursive
	 *  code rather than unrolled case
	 *
	 *  Recursive invocations don't need to erase the cursor over and
	 *  over again, so we use fbcon_bmove_rec()
	 */
	fbcon_bmove_rec(vc, p, sy, sx, dy, dx, height, width,
			p->vrows - p->yscroll);
}