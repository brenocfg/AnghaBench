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
struct TYPE_2__ {int line_length; int /*<<< orphan*/  accel; int /*<<< orphan*/  visual; int /*<<< orphan*/  type; int /*<<< orphan*/  id; } ;
struct fb_info {TYPE_1__ fix; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FB_ACCEL_SUN_CGTHREE ; 
 int /*<<< orphan*/  FB_TYPE_PACKED_PIXELS ; 
 int /*<<< orphan*/  FB_VISUAL_PSEUDOCOLOR ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,struct device_node*) ; 

__attribute__((used)) static void cg3_init_fix(struct fb_info *info, int linebytes,
			 struct device_node *dp)
{
	snprintf(info->fix.id, sizeof(info->fix.id), "%pOFn", dp);

	info->fix.type = FB_TYPE_PACKED_PIXELS;
	info->fix.visual = FB_VISUAL_PSEUDOCOLOR;

	info->fix.line_length = linebytes;

	info->fix.accel = FB_ACCEL_SUN_CGTHREE;
}