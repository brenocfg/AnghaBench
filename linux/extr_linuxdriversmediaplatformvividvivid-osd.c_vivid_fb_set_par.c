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
struct vivid_dev {int dummy; } ;
struct fb_info {int /*<<< orphan*/  fix; int /*<<< orphan*/  var; scalar_t__ par; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (struct vivid_dev*,int,char*) ; 
 int /*<<< orphan*/  vivid_fb_get_fix (struct vivid_dev*,int /*<<< orphan*/ *) ; 
 int vivid_fb_set_var (struct vivid_dev*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vivid_fb_set_par(struct fb_info *info)
{
	int rc = 0;
	struct vivid_dev *dev = (struct vivid_dev *) info->par;

	dprintk(dev, 1, "vivid_fb_set_par\n");

	rc = vivid_fb_set_var(dev, &info->var);
	vivid_fb_get_fix(dev, &info->fix);
	return rc;
}