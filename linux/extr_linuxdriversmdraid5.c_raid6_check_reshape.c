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
struct mddev {int new_chunk_sectors; scalar_t__ new_layout; int array_sectors; } ;

/* Variables and functions */
 int EINVAL ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  algorithm_valid_raid6 (scalar_t__) ; 
 int check_reshape (struct mddev*) ; 
 int /*<<< orphan*/  is_power_of_2 (int) ; 

__attribute__((used)) static int raid6_check_reshape(struct mddev *mddev)
{
	int new_chunk = mddev->new_chunk_sectors;

	if (mddev->new_layout >= 0 && !algorithm_valid_raid6(mddev->new_layout))
		return -EINVAL;
	if (new_chunk > 0) {
		if (!is_power_of_2(new_chunk))
			return -EINVAL;
		if (new_chunk < (PAGE_SIZE >> 9))
			return -EINVAL;
		if (mddev->array_sectors & (new_chunk-1))
			/* not factor of array size */
			return -EINVAL;
	}

	/* They look valid */
	return check_reshape(mddev);
}