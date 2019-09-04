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
struct ivtv {int dummy; } ;
struct fb_info {int /*<<< orphan*/  fix; int /*<<< orphan*/  var; scalar_t__ par; } ;

/* Variables and functions */
 int /*<<< orphan*/  IVTVFB_DEBUG_INFO (char*) ; 
 int /*<<< orphan*/  ivtv_firmware_check (struct ivtv*,char*) ; 
 int /*<<< orphan*/  ivtvfb_get_fix (struct ivtv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ivtvfb_pan_display (int /*<<< orphan*/ *,struct fb_info*) ; 
 int ivtvfb_set_var (struct ivtv*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ivtvfb_set_par(struct fb_info *info)
{
	int rc = 0;
	struct ivtv *itv = (struct ivtv *) info->par;

	IVTVFB_DEBUG_INFO("ivtvfb_set_par\n");

	rc = ivtvfb_set_var(itv, &info->var);
	ivtvfb_pan_display(&info->var, info);
	ivtvfb_get_fix(itv, &info->fix);
	ivtv_firmware_check(itv, "ivtvfb_set_par");
	return rc;
}