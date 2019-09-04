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
struct v3d_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int V3D_CORE_READ (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V3D_CORE_WRITE (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  V3D_CTL_L2TCACTL ; 
 int /*<<< orphan*/  V3D_L2TCACTL_FLM ; 
 int /*<<< orphan*/  V3D_L2TCACTL_FLM_CLEAR ; 
 int V3D_L2TCACTL_L2TFLS ; 
 int V3D_SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ wait_for (int,int) ; 

__attribute__((used)) static void
v3d_invalidate_l2t(struct v3d_dev *v3d, int core)
{
	V3D_CORE_WRITE(core,
		       V3D_CTL_L2TCACTL,
		       V3D_L2TCACTL_L2TFLS |
		       V3D_SET_FIELD(V3D_L2TCACTL_FLM_CLEAR, V3D_L2TCACTL_FLM));
	if (wait_for(!(V3D_CORE_READ(core, V3D_CTL_L2TCACTL) &
		       V3D_L2TCACTL_L2TFLS), 100)) {
		DRM_ERROR("Timeout waiting for L2T invalidate\n");
	}
}