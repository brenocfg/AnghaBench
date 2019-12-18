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
 int /*<<< orphan*/  V3D_CORE_WRITE (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V3D_GMP_CFG ; 
 int /*<<< orphan*/  V3D_GMP_CFG_STOP_REQ ; 
 int /*<<< orphan*/  V3D_GMP_STATUS ; 
 int V3D_GMP_STATUS_CFG_BUSY ; 
 int V3D_GMP_STATUS_RD_COUNT_MASK ; 
 int V3D_GMP_STATUS_WR_COUNT_MASK ; 
 scalar_t__ wait_for (int,int) ; 

__attribute__((used)) static void
v3d_idle_axi(struct v3d_dev *v3d, int core)
{
	V3D_CORE_WRITE(core, V3D_GMP_CFG, V3D_GMP_CFG_STOP_REQ);

	if (wait_for((V3D_CORE_READ(core, V3D_GMP_STATUS) &
		      (V3D_GMP_STATUS_RD_COUNT_MASK |
		       V3D_GMP_STATUS_WR_COUNT_MASK |
		       V3D_GMP_STATUS_CFG_BUSY)) == 0, 100)) {
		DRM_ERROR("Failed to wait for safe GMP shutdown\n");
	}
}