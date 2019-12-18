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
struct omapfb_info {int /*<<< orphan*/  region; int /*<<< orphan*/  id; } ;
struct fb_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ) ; 
 struct omapfb_info* FB2OFB (struct fb_info*) ; 
 int omapfb_apply_changes (struct fb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omapfb_get_mem_region (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omapfb_put_mem_region (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_fb_fix (struct fb_info*) ; 
 int setup_vrfb_rotation (struct fb_info*) ; 

__attribute__((used)) static int omapfb_set_par(struct fb_info *fbi)
{
	struct omapfb_info *ofbi = FB2OFB(fbi);
	int r;

	DBG("set_par(%d)\n", FB2OFB(fbi)->id);

	omapfb_get_mem_region(ofbi->region);

	set_fb_fix(fbi);

	r = setup_vrfb_rotation(fbi);
	if (r)
		goto out;

	r = omapfb_apply_changes(fbi, 0);

 out:
	omapfb_put_mem_region(ofbi->region);

	return r;
}