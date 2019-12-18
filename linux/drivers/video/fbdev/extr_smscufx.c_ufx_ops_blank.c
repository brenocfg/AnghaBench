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
struct ufx_data {int dummy; } ;
struct fb_info {int /*<<< orphan*/  var; struct ufx_data* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  ufx_set_vid_mode (struct ufx_data*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ufx_ops_blank(int blank_mode, struct fb_info *info)
{
	struct ufx_data *dev = info->par;
	ufx_set_vid_mode(dev, &info->var);
	return 0;
}