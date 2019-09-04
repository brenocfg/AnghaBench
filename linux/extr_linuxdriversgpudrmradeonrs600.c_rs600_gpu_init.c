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
struct radeon_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  r420_pipes_init (struct radeon_device*) ; 
 scalar_t__ rs600_mc_wait_for_idle (struct radeon_device*) ; 

__attribute__((used)) static void rs600_gpu_init(struct radeon_device *rdev)
{
	r420_pipes_init(rdev);
	/* Wait for mc idle */
	if (rs600_mc_wait_for_idle(rdev))
		dev_warn(rdev->dev, "Wait MC idle timeout before updating MC.\n");
}