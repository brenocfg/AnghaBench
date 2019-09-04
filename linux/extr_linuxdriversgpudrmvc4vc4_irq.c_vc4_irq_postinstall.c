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
struct vc4_dev {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  V3D_DRIVER_IRQS ; 
 int /*<<< orphan*/  V3D_INTENA ; 
 int /*<<< orphan*/  V3D_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vc4_dev* to_vc4_dev (struct drm_device*) ; 

int
vc4_irq_postinstall(struct drm_device *dev)
{
	struct vc4_dev *vc4 = to_vc4_dev(dev);

	/* Enable both the render done and out of memory interrupts. */
	V3D_WRITE(V3D_INTENA, V3D_DRIVER_IRQS);

	return 0;
}