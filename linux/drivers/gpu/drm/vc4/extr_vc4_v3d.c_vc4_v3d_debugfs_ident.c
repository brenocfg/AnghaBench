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
typedef  int uint32_t ;
struct vc4_dev {int dummy; } ;
struct seq_file {scalar_t__ private; } ;
struct drm_info_node {TYPE_1__* minor; } ;
struct drm_device {int dummy; } ;
struct TYPE_2__ {struct drm_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  V3D_IDENT1 ; 
 int /*<<< orphan*/  V3D_IDENT1_NSEM ; 
 int /*<<< orphan*/  V3D_IDENT1_NSLC ; 
 int /*<<< orphan*/  V3D_IDENT1_QUPS ; 
 int /*<<< orphan*/  V3D_IDENT1_REV ; 
 int /*<<< orphan*/  V3D_IDENT1_TUPS ; 
 int V3D_READ (int /*<<< orphan*/ ) ; 
 int VC4_GET_FIELD (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int) ; 
 struct vc4_dev* to_vc4_dev (struct drm_device*) ; 
 int vc4_v3d_pm_get (struct vc4_dev*) ; 
 int /*<<< orphan*/  vc4_v3d_pm_put (struct vc4_dev*) ; 

__attribute__((used)) static int vc4_v3d_debugfs_ident(struct seq_file *m, void *unused)
{
	struct drm_info_node *node = (struct drm_info_node *)m->private;
	struct drm_device *dev = node->minor->dev;
	struct vc4_dev *vc4 = to_vc4_dev(dev);
	int ret = vc4_v3d_pm_get(vc4);

	if (ret == 0) {
		uint32_t ident1 = V3D_READ(V3D_IDENT1);
		uint32_t nslc = VC4_GET_FIELD(ident1, V3D_IDENT1_NSLC);
		uint32_t tups = VC4_GET_FIELD(ident1, V3D_IDENT1_TUPS);
		uint32_t qups = VC4_GET_FIELD(ident1, V3D_IDENT1_QUPS);

		seq_printf(m, "Revision:   %d\n",
			   VC4_GET_FIELD(ident1, V3D_IDENT1_REV));
		seq_printf(m, "Slices:     %d\n", nslc);
		seq_printf(m, "TMUs:       %d\n", nslc * tups);
		seq_printf(m, "QPUs:       %d\n", nslc * qups);
		seq_printf(m, "Semaphores: %d\n",
			   VC4_GET_FIELD(ident1, V3D_IDENT1_NSEM));
		vc4_v3d_pm_put(vc4);
	}

	return 0;
}