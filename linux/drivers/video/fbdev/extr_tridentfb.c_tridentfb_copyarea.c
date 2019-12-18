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
struct tridentfb_par {int /*<<< orphan*/  (* copy_rect ) (struct tridentfb_par*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* wait_engine ) (struct tridentfb_par*) ;} ;
struct fb_info {int flags; struct tridentfb_par* par; } ;
struct fb_copyarea {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  dy; int /*<<< orphan*/  dx; int /*<<< orphan*/  sy; int /*<<< orphan*/  sx; } ;

/* Variables and functions */
 int FBINFO_HWACCEL_DISABLED ; 
 int /*<<< orphan*/  cfb_copyarea (struct fb_info*,struct fb_copyarea const*) ; 
 int /*<<< orphan*/  stub1 (struct tridentfb_par*) ; 
 int /*<<< orphan*/  stub2 (struct tridentfb_par*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tridentfb_copyarea(struct fb_info *info,
			       const struct fb_copyarea *ca)
{
	struct tridentfb_par *par = info->par;

	if (info->flags & FBINFO_HWACCEL_DISABLED) {
		cfb_copyarea(info, ca);
		return;
	}
	par->wait_engine(par);
	par->copy_rect(par, ca->sx, ca->sy, ca->dx, ca->dy,
		       ca->width, ca->height);
}