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
struct iio_dev {int /*<<< orphan*/  available_scan_masks; } ;

/* Variables and functions */
 int /*<<< orphan*/  bitmap_free (unsigned long const*) ; 

__attribute__((used)) static void iio_free_scan_mask(struct iio_dev *indio_dev,
	const unsigned long *mask)
{
	/* If the mask is dynamically allocated free it, otherwise do nothing */
	if (!indio_dev->available_scan_masks)
		bitmap_free(mask);
}