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
struct omapfb_plane_struct {size_t idx; struct omapfb_device* fbdev; } ;
struct omapfb_mem_region {int /*<<< orphan*/  type; int /*<<< orphan*/  size; } ;
struct omapfb_mem_info {int /*<<< orphan*/  type; int /*<<< orphan*/  size; } ;
struct TYPE_2__ {struct omapfb_mem_region* region; } ;
struct omapfb_device {TYPE_1__ mem_desc; } ;
struct fb_info {struct omapfb_plane_struct* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct omapfb_mem_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int omapfb_query_mem(struct fb_info *fbi, struct omapfb_mem_info *mi)
{
	struct omapfb_plane_struct *plane = fbi->par;
	struct omapfb_device *fbdev = plane->fbdev;
	struct omapfb_mem_region *rg;

	rg = &fbdev->mem_desc.region[plane->idx];
	memset(mi, 0, sizeof(*mi));
	mi->size = rg->size;
	mi->type = rg->type;

	return 0;
}