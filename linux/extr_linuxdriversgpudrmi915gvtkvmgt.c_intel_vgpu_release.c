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
struct mdev_device {int dummy; } ;
struct intel_vgpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __intel_vgpu_release (struct intel_vgpu*) ; 
 struct intel_vgpu* mdev_get_drvdata (struct mdev_device*) ; 

__attribute__((used)) static void intel_vgpu_release(struct mdev_device *mdev)
{
	struct intel_vgpu *vgpu = mdev_get_drvdata(mdev);

	__intel_vgpu_release(vgpu);
}