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
typedef  int u32 ;
struct TYPE_4__ {int y; int cb; int cr; } ;
struct gsc_frame {int* payload; TYPE_2__ addr; TYPE_1__* fmt; } ;
struct gsc_dev {int dummy; } ;
struct TYPE_3__ {int num_planes; } ;

/* Variables and functions */
 scalar_t__ get_plane_info (struct gsc_frame*,int,int*,int*) ; 
 int max3 (int,int,int) ; 
 int min3 (int,int,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int,int,int) ; 

void gsc_set_prefbuf(struct gsc_dev *gsc, struct gsc_frame *frm)
{
	u32 f_chk_addr, f_chk_len, s_chk_addr, s_chk_len;
	f_chk_addr = f_chk_len = s_chk_addr = s_chk_len = 0;

	f_chk_addr = frm->addr.y;
	f_chk_len = frm->payload[0];
	if (frm->fmt->num_planes == 2) {
		s_chk_addr = frm->addr.cb;
		s_chk_len = frm->payload[1];
	} else if (frm->fmt->num_planes == 3) {
		u32 low_addr, low_plane, mid_addr, mid_plane;
		u32 high_addr, high_plane;
		u32 t_min, t_max;

		t_min = min3(frm->addr.y, frm->addr.cb, frm->addr.cr);
		if (get_plane_info(frm, t_min, &low_plane, &low_addr))
			return;
		t_max = max3(frm->addr.y, frm->addr.cb, frm->addr.cr);
		if (get_plane_info(frm, t_max, &high_plane, &high_addr))
			return;

		mid_plane = 3 - (low_plane + high_plane);
		if (mid_plane == 0)
			mid_addr = frm->addr.y;
		else if (mid_plane == 1)
			mid_addr = frm->addr.cb;
		else if (mid_plane == 2)
			mid_addr = frm->addr.cr;
		else
			return;

		f_chk_addr = low_addr;
		if (mid_addr + frm->payload[mid_plane] - low_addr >
		    high_addr + frm->payload[high_plane] - mid_addr) {
			f_chk_len = frm->payload[low_plane];
			s_chk_addr = mid_addr;
			s_chk_len = high_addr +
					frm->payload[high_plane] - mid_addr;
		} else {
			f_chk_len = mid_addr +
					frm->payload[mid_plane] - low_addr;
			s_chk_addr = high_addr;
			s_chk_len = frm->payload[high_plane];
		}
	}
	pr_debug("f_addr = 0x%08x, f_len = %d, s_addr = 0x%08x, s_len = %d\n",
			f_chk_addr, f_chk_len, s_chk_addr, s_chk_len);
}