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
typedef  int /*<<< orphan*/  uint32_t ;
struct vc4_dev {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  V3D_CTNCA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V3D_CTNEA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V3D_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vc4_dev* to_vc4_dev (struct drm_device*) ; 

__attribute__((used)) static void
submit_cl(struct drm_device *dev, uint32_t thread, uint32_t start, uint32_t end)
{
	struct vc4_dev *vc4 = to_vc4_dev(dev);

	/* Set the current and end address of the control list.
	 * Writing the end register is what starts the job.
	 */
	V3D_WRITE(V3D_CTNCA(thread), start);
	V3D_WRITE(V3D_CTNEA(thread), end);
}