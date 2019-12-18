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
typedef  int /*<<< orphan*/  u32 ;
struct video_frame {int dummy; } ;
struct tegra_vde {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  tegra_vde_setup_frameid (struct tegra_vde*,struct video_frame*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tegra_setup_frameidx(struct tegra_vde *vde,
				 struct video_frame *frames,
				 unsigned int frames_nb,
				 u32 mbs_width, u32 mbs_height)
{
	unsigned int idx;

	for (idx = 0; idx < frames_nb; idx++)
		tegra_vde_setup_frameid(vde, &frames[idx], idx,
					mbs_width, mbs_height);

	for (; idx < 17; idx++)
		tegra_vde_setup_frameid(vde, NULL, idx, 0, 0);
}