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
struct opal_dev {int /*<<< orphan*/  lowest_lba; int /*<<< orphan*/  align; } ;
struct d0_geometry_features {int /*<<< orphan*/  lowest_aligned_lba; int /*<<< orphan*/  alignment_granularity; } ;

/* Variables and functions */

__attribute__((used)) static void check_geometry(struct opal_dev *dev, const void *data)
{
	const struct d0_geometry_features *geo = data;

	dev->align = geo->alignment_granularity;
	dev->lowest_lba = geo->lowest_aligned_lba;
}