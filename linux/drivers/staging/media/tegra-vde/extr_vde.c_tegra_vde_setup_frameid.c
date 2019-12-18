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
typedef  int u32 ;
struct video_frame {int y_addr; int cb_addr; int cr_addr; } ;
struct tegra_vde {int /*<<< orphan*/  frameid; } ;

/* Variables and functions */
 int /*<<< orphan*/  tegra_vde_writel (struct tegra_vde*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void tegra_vde_setup_frameid(struct tegra_vde *vde,
				    struct video_frame *frame,
				    unsigned int frameid,
				    u32 mbs_width, u32 mbs_height)
{
	u32 y_addr  = frame ? frame->y_addr  : 0x6CDEAD00;
	u32 cb_addr = frame ? frame->cb_addr : 0x6CDEAD00;
	u32 cr_addr = frame ? frame->cr_addr : 0x6CDEAD00;
	u32 value1 = frame ? ((mbs_width << 16) | mbs_height) : 0;
	u32 value2 = frame ? ((((mbs_width + 1) >> 1) << 6) | 1) : 0;

	tegra_vde_writel(vde, y_addr  >> 8, vde->frameid, 0x000 + frameid * 4);
	tegra_vde_writel(vde, cb_addr >> 8, vde->frameid, 0x100 + frameid * 4);
	tegra_vde_writel(vde, cr_addr >> 8, vde->frameid, 0x180 + frameid * 4);
	tegra_vde_writel(vde, value1,       vde->frameid, 0x080 + frameid * 4);
	tegra_vde_writel(vde, value2,       vde->frameid, 0x280 + frameid * 4);
}