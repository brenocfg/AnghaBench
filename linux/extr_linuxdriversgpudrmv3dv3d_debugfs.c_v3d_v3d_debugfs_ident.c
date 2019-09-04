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
typedef  int u32 ;
struct v3d_dev {int /*<<< orphan*/  dev; } ;
struct seq_file {scalar_t__ private; } ;
struct drm_info_node {TYPE_1__* minor; } ;
struct drm_device {int dummy; } ;
struct TYPE_2__ {struct drm_device* dev; } ;

/* Variables and functions */
 int V3D_CORE_READ (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V3D_CTL_IDENT0 ; 
 int /*<<< orphan*/  V3D_CTL_IDENT1 ; 
 int /*<<< orphan*/  V3D_CTL_IDENT2 ; 
 int /*<<< orphan*/  V3D_CTL_MISCCFG ; 
 int V3D_GET_FIELD (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V3D_HUB_IDENT0 ; 
 int /*<<< orphan*/  V3D_HUB_IDENT1 ; 
 int /*<<< orphan*/  V3D_HUB_IDENT1_NCORES ; 
 int /*<<< orphan*/  V3D_HUB_IDENT1_REV ; 
 int /*<<< orphan*/  V3D_HUB_IDENT1_TVER ; 
 int V3D_HUB_IDENT1_WITH_L3C ; 
 int V3D_HUB_IDENT1_WITH_MSO ; 
 int V3D_HUB_IDENT1_WITH_TFU ; 
 int V3D_HUB_IDENT1_WITH_TSY ; 
 int /*<<< orphan*/  V3D_HUB_IDENT2 ; 
 int /*<<< orphan*/  V3D_HUB_IDENT2_L3C_NKB ; 
 int V3D_HUB_IDENT2_WITH_MMU ; 
 int /*<<< orphan*/  V3D_HUB_IDENT3 ; 
 int /*<<< orphan*/  V3D_HUB_IDENT3_IPIDX ; 
 int /*<<< orphan*/  V3D_HUB_IDENT3_IPREV ; 
 int /*<<< orphan*/  V3D_IDENT0_VER ; 
 int /*<<< orphan*/  V3D_IDENT1_NSEM ; 
 int /*<<< orphan*/  V3D_IDENT1_NSLC ; 
 int /*<<< orphan*/  V3D_IDENT1_NTMU ; 
 int /*<<< orphan*/  V3D_IDENT1_QUPS ; 
 int /*<<< orphan*/  V3D_IDENT1_REV ; 
 int V3D_IDENT2_BCG_INT ; 
 int V3D_MISCCFG_OVRTMUOUT ; 
 int V3D_READ (int /*<<< orphan*/ ) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 
 struct v3d_dev* to_v3d_dev (struct drm_device*) ; 

__attribute__((used)) static int v3d_v3d_debugfs_ident(struct seq_file *m, void *unused)
{
	struct drm_info_node *node = (struct drm_info_node *)m->private;
	struct drm_device *dev = node->minor->dev;
	struct v3d_dev *v3d = to_v3d_dev(dev);
	u32 ident0, ident1, ident2, ident3, cores;
	int ret, core;

	ret = pm_runtime_get_sync(v3d->dev);
	if (ret < 0)
		return ret;

	ident0 = V3D_READ(V3D_HUB_IDENT0);
	ident1 = V3D_READ(V3D_HUB_IDENT1);
	ident2 = V3D_READ(V3D_HUB_IDENT2);
	ident3 = V3D_READ(V3D_HUB_IDENT3);
	cores = V3D_GET_FIELD(ident1, V3D_HUB_IDENT1_NCORES);

	seq_printf(m, "Revision:   %d.%d.%d.%d\n",
		   V3D_GET_FIELD(ident1, V3D_HUB_IDENT1_TVER),
		   V3D_GET_FIELD(ident1, V3D_HUB_IDENT1_REV),
		   V3D_GET_FIELD(ident3, V3D_HUB_IDENT3_IPREV),
		   V3D_GET_FIELD(ident3, V3D_HUB_IDENT3_IPIDX));
	seq_printf(m, "MMU:        %s\n",
		   (ident2 & V3D_HUB_IDENT2_WITH_MMU) ? "yes" : "no");
	seq_printf(m, "TFU:        %s\n",
		   (ident1 & V3D_HUB_IDENT1_WITH_TFU) ? "yes" : "no");
	seq_printf(m, "TSY:        %s\n",
		   (ident1 & V3D_HUB_IDENT1_WITH_TSY) ? "yes" : "no");
	seq_printf(m, "MSO:        %s\n",
		   (ident1 & V3D_HUB_IDENT1_WITH_MSO) ? "yes" : "no");
	seq_printf(m, "L3C:        %s (%dkb)\n",
		   (ident1 & V3D_HUB_IDENT1_WITH_L3C) ? "yes" : "no",
		   V3D_GET_FIELD(ident2, V3D_HUB_IDENT2_L3C_NKB));

	for (core = 0; core < cores; core++) {
		u32 misccfg;
		u32 nslc, ntmu, qups;

		ident0 = V3D_CORE_READ(core, V3D_CTL_IDENT0);
		ident1 = V3D_CORE_READ(core, V3D_CTL_IDENT1);
		ident2 = V3D_CORE_READ(core, V3D_CTL_IDENT2);
		misccfg = V3D_CORE_READ(core, V3D_CTL_MISCCFG);

		nslc = V3D_GET_FIELD(ident1, V3D_IDENT1_NSLC);
		ntmu = V3D_GET_FIELD(ident1, V3D_IDENT1_NTMU);
		qups = V3D_GET_FIELD(ident1, V3D_IDENT1_QUPS);

		seq_printf(m, "Core %d:\n", core);
		seq_printf(m, "  Revision:     %d.%d\n",
			   V3D_GET_FIELD(ident0, V3D_IDENT0_VER),
			   V3D_GET_FIELD(ident1, V3D_IDENT1_REV));
		seq_printf(m, "  Slices:       %d\n", nslc);
		seq_printf(m, "  TMUs:         %d\n", nslc * ntmu);
		seq_printf(m, "  QPUs:         %d\n", nslc * qups);
		seq_printf(m, "  Semaphores:   %d\n",
			   V3D_GET_FIELD(ident1, V3D_IDENT1_NSEM));
		seq_printf(m, "  BCG int:      %d\n",
			   (ident2 & V3D_IDENT2_BCG_INT) != 0);
		seq_printf(m, "  Override TMU: %d\n",
			   (misccfg & V3D_MISCCFG_OVRTMUOUT) != 0);
	}

	pm_runtime_mark_last_busy(v3d->dev);
	pm_runtime_put_autosuspend(v3d->dev);

	return 0;
}