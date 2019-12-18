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
struct vc4_dev {int /*<<< orphan*/  v3d; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  V3D_INTENA ; 
 int V3D_INT_FLDONE ; 
 int V3D_INT_FRDONE ; 
 int /*<<< orphan*/  V3D_WRITE (int /*<<< orphan*/ ,int) ; 
 struct vc4_dev* to_vc4_dev (struct drm_device*) ; 

int
vc4_irq_postinstall(struct drm_device *dev)
{
	struct vc4_dev *vc4 = to_vc4_dev(dev);

	if (!vc4->v3d)
		return 0;

	/* Enable the render done interrupts. The out-of-memory interrupt is
	 * enabled as soon as we have a binner BO allocated.
	 */
	V3D_WRITE(V3D_INTENA, V3D_INT_FLDONE | V3D_INT_FRDONE);

	return 0;
}