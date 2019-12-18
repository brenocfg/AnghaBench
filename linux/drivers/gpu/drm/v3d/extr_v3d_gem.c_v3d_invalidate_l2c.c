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
struct v3d_dev {int ver; } ;

/* Variables and functions */
 int /*<<< orphan*/  V3D_CORE_WRITE (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  V3D_CTL_L2CACTL ; 
 int V3D_L2CACTL_L2CCLR ; 
 int V3D_L2CACTL_L2CENA ; 

__attribute__((used)) static void
v3d_invalidate_l2c(struct v3d_dev *v3d, int core)
{
	if (v3d->ver > 32)
		return;

	V3D_CORE_WRITE(core, V3D_CTL_L2CACTL,
		       V3D_L2CACTL_L2CCLR |
		       V3D_L2CACTL_L2CENA);
}