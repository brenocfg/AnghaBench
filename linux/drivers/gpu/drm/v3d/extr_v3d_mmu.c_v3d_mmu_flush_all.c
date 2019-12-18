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
struct v3d_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  V3D_MMUC_CONTROL ; 
 int V3D_MMUC_CONTROL_ENABLE ; 
 int V3D_MMUC_CONTROL_FLUSH ; 
 int V3D_MMUC_CONTROL_FLUSHING ; 
 int /*<<< orphan*/  V3D_MMU_CTL ; 
 int V3D_MMU_CTL_TLB_CLEAR ; 
 int V3D_MMU_CTL_TLB_CLEARING ; 
 int V3D_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V3D_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int wait_for (int,int) ; 

__attribute__((used)) static int v3d_mmu_flush_all(struct v3d_dev *v3d)
{
	int ret;

	/* Make sure that another flush isn't already running when we
	 * start this one.
	 */
	ret = wait_for(!(V3D_READ(V3D_MMU_CTL) &
			 V3D_MMU_CTL_TLB_CLEARING), 100);
	if (ret)
		dev_err(v3d->dev, "TLB clear wait idle pre-wait failed\n");

	V3D_WRITE(V3D_MMU_CTL, V3D_READ(V3D_MMU_CTL) |
		  V3D_MMU_CTL_TLB_CLEAR);

	V3D_WRITE(V3D_MMUC_CONTROL,
		  V3D_MMUC_CONTROL_FLUSH |
		  V3D_MMUC_CONTROL_ENABLE);

	ret = wait_for(!(V3D_READ(V3D_MMU_CTL) &
			 V3D_MMU_CTL_TLB_CLEARING), 100);
	if (ret) {
		dev_err(v3d->dev, "TLB clear wait idle failed\n");
		return ret;
	}

	ret = wait_for(!(V3D_READ(V3D_MMUC_CONTROL) &
			 V3D_MMUC_CONTROL_FLUSHING), 100);
	if (ret)
		dev_err(v3d->dev, "MMUC flush wait idle failed\n");

	return ret;
}