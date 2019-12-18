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
struct fbcon_ops {int /*<<< orphan*/ * p; } ;
struct fb_info {int /*<<< orphan*/  flags; struct fbcon_ops* fbcon_par; } ;

/* Variables and functions */
 int /*<<< orphan*/  FBINFO_MISC_TILEBLITTING ; 
 int /*<<< orphan*/ * fb_display ; 
 int /*<<< orphan*/  fbcon_set_bitops (struct fbcon_ops*) ; 
 int /*<<< orphan*/  fbcon_set_rotation (struct fb_info*) ; 

__attribute__((used)) static void set_blitting_type(struct vc_data *vc, struct fb_info *info)
{
	struct fbcon_ops *ops = info->fbcon_par;

	info->flags &= ~FBINFO_MISC_TILEBLITTING;
	ops->p = &fb_display[vc->vc_num];
	fbcon_set_rotation(info);
	fbcon_set_bitops(ops);
}