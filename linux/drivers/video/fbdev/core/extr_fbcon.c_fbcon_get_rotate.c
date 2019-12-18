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
struct fbcon_ops {int rotate; } ;
struct fb_info {struct fbcon_ops* fbcon_par; } ;

/* Variables and functions */

__attribute__((used)) static int fbcon_get_rotate(struct fb_info *info)
{
	struct fbcon_ops *ops = info->fbcon_par;

	return (ops) ? ops->rotate : 0;
}