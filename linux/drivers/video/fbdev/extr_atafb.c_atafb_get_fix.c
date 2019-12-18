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
struct fb_info {int /*<<< orphan*/  var; } ;
struct fb_fix_screeninfo {int dummy; } ;
struct atafb_par {int dummy; } ;
struct TYPE_2__ {int (* decode_var ) (int /*<<< orphan*/ *,struct atafb_par*) ;int (* encode_fix ) (struct fb_fix_screeninfo*,struct atafb_par*) ;} ;

/* Variables and functions */
 TYPE_1__* fbhw ; 
 int /*<<< orphan*/  memset (struct fb_fix_screeninfo*,int /*<<< orphan*/ ,int) ; 
 int stub1 (int /*<<< orphan*/ *,struct atafb_par*) ; 
 int stub2 (struct fb_fix_screeninfo*,struct atafb_par*) ; 

__attribute__((used)) static int atafb_get_fix(struct fb_fix_screeninfo *fix, struct fb_info *info)
{
	struct atafb_par par;
	int err;
	// Get fix directly (case con == -1 before)??
	err = fbhw->decode_var(&info->var, &par);
	if (err)
		return err;
	memset(fix, 0, sizeof(struct fb_fix_screeninfo));
	err = fbhw->encode_fix(fix, &par);
	return err;
}