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
struct TYPE_2__ {unsigned int max_handles; int* img_size; int /*<<< orphan*/ * handles; } ;
struct radeon_device {TYPE_1__ uvd; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void radeon_uvd_count_handles(struct radeon_device *rdev,
				     unsigned *sd, unsigned *hd)
{
	unsigned i;

	*sd = 0;
	*hd = 0;

	for (i = 0; i < rdev->uvd.max_handles; ++i) {
		if (!atomic_read(&rdev->uvd.handles[i]))
			continue;

		if (rdev->uvd.img_size[i] >= 720*576)
			++(*hd);
		else
			++(*sd);
	}
}