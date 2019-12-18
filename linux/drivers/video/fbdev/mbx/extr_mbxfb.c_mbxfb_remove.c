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
struct platform_device {int dummy; } ;
struct mbxfb_info {TYPE_1__* fb_req; TYPE_1__* reg_req; int /*<<< orphan*/  (* platform_remove ) (struct fb_info*) ;} ;
struct fb_info {struct mbxfb_info* par; } ;
struct TYPE_2__ {int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYSRST ; 
 int /*<<< orphan*/  SYSRST_RST ; 
 int /*<<< orphan*/  framebuffer_release (struct fb_info*) ; 
 int /*<<< orphan*/  mbxfb_debugfs_remove (struct fb_info*) ; 
 struct fb_info* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  res_size (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (struct fb_info*) ; 
 int /*<<< orphan*/  unregister_framebuffer (struct fb_info*) ; 
 int /*<<< orphan*/  write_reg_dly (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mbxfb_remove(struct platform_device *dev)
{
	struct fb_info *fbi = platform_get_drvdata(dev);

	write_reg_dly(SYSRST_RST, SYSRST);

	mbxfb_debugfs_remove(fbi);

	if (fbi) {
		struct mbxfb_info *mfbi = fbi->par;

		unregister_framebuffer(fbi);
		if (mfbi) {
			if (mfbi->platform_remove)
				mfbi->platform_remove(fbi);


			if (mfbi->reg_req)
				release_mem_region(mfbi->reg_req->start,
						   res_size(mfbi->reg_req));
			if (mfbi->fb_req)
				release_mem_region(mfbi->fb_req->start,
						   res_size(mfbi->fb_req));
		}
		framebuffer_release(fbi);
	}

	return 0;
}