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
struct drm_mm {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  drm_mm_init (struct drm_mm*,unsigned int const,unsigned int const) ; 
 int /*<<< orphan*/  drm_mm_takedown (struct drm_mm*) ; 
 int /*<<< orphan*/  expect_insert_in_range_fail (struct drm_mm*,unsigned int const,unsigned int const,unsigned int const) ; 

__attribute__((used)) static int insert_outside_range(void)
{
	struct drm_mm mm;
	const unsigned int start = 1024;
	const unsigned int end = 2048;
	const unsigned int size = end - start;

	drm_mm_init(&mm, start, size);

	if (!expect_insert_in_range_fail(&mm, 1, 0, start))
		return -EINVAL;

	if (!expect_insert_in_range_fail(&mm, size,
					 start - size/2, start + (size+1)/2))
		return -EINVAL;

	if (!expect_insert_in_range_fail(&mm, size,
					 end - (size+1)/2, end + size/2))
		return -EINVAL;

	if (!expect_insert_in_range_fail(&mm, 1, end, end + size))
		return -EINVAL;

	drm_mm_takedown(&mm);
	return 0;
}