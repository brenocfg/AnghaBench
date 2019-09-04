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
struct osd_info {int* palette_cur; int pan_cur; int /*<<< orphan*/  ivtvfb_info; int /*<<< orphan*/  blank_cur; int /*<<< orphan*/  fbvar_cur; } ;
struct ivtv {struct osd_info* osd_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  ivtvfb_blank (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ivtvfb_set_var (struct ivtv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_reg (int,int) ; 

__attribute__((used)) static void ivtvfb_restore(struct ivtv *itv)
{
	struct osd_info *oi = itv->osd_info;
	int i;

	ivtvfb_set_var(itv, &oi->fbvar_cur);
	ivtvfb_blank(oi->blank_cur, &oi->ivtvfb_info);
	for (i = 0; i < 256; i++) {
		write_reg(i, 0x02a30);
		write_reg(oi->palette_cur[i], 0x02a34);
	}
	write_reg(oi->pan_cur, 0x02a0c);
}