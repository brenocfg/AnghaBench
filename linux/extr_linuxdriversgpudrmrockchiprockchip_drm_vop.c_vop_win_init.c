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
struct vop_win_data {int dummy; } ;
struct vop_win {struct vop* vop; struct vop_win_data const* data; } ;
struct vop_data {unsigned int win_size; struct vop_win_data* win; } ;
struct vop {struct vop_win* win; struct vop_data* data; } ;

/* Variables and functions */

__attribute__((used)) static void vop_win_init(struct vop *vop)
{
	const struct vop_data *vop_data = vop->data;
	unsigned int i;

	for (i = 0; i < vop_data->win_size; i++) {
		struct vop_win *vop_win = &vop->win[i];
		const struct vop_win_data *win_data = &vop_data->win[i];

		vop_win->data = win_data;
		vop_win->vop = vop;
	}
}