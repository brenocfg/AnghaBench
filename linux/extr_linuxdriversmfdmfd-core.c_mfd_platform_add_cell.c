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
struct platform_device {TYPE_1__* mfd_cell; } ;
struct mfd_cell {int dummy; } ;
typedef  int /*<<< orphan*/  atomic_t ;
struct TYPE_2__ {int /*<<< orphan*/ * usage_count; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_1__* kmemdup (struct mfd_cell const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mfd_platform_add_cell(struct platform_device *pdev,
				 const struct mfd_cell *cell,
				 atomic_t *usage_count)
{
	if (!cell)
		return 0;

	pdev->mfd_cell = kmemdup(cell, sizeof(*cell), GFP_KERNEL);
	if (!pdev->mfd_cell)
		return -ENOMEM;

	pdev->mfd_cell->usage_count = usage_count;
	return 0;
}