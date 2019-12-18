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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ y; scalar_t__ cb; scalar_t__ cr; } ;
struct gsc_frame {TYPE_1__ addr; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int get_plane_info(struct gsc_frame *frm, u32 addr, u32 *index, u32 *ret_addr)
{
	if (frm->addr.y == addr) {
		*index = 0;
		*ret_addr = frm->addr.y;
	} else if (frm->addr.cb == addr) {
		*index = 1;
		*ret_addr = frm->addr.cb;
	} else if (frm->addr.cr == addr) {
		*index = 2;
		*ret_addr = frm->addr.cr;
	} else {
		pr_err("Plane address is wrong");
		return -EINVAL;
	}
	return 0;
}