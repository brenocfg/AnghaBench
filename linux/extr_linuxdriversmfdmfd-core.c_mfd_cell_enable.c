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
struct platform_device {int dummy; } ;
struct mfd_cell {int (* enable ) (struct platform_device*) ;int /*<<< orphan*/  usage_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ ) ; 
 int atomic_inc_return (int /*<<< orphan*/ ) ; 
 struct mfd_cell* mfd_get_cell (struct platform_device*) ; 
 int stub1 (struct platform_device*) ; 

int mfd_cell_enable(struct platform_device *pdev)
{
	const struct mfd_cell *cell = mfd_get_cell(pdev);
	int err = 0;

	/* only call enable hook if the cell wasn't previously enabled */
	if (atomic_inc_return(cell->usage_count) == 1)
		err = cell->enable(pdev);

	/* if the enable hook failed, decrement counter to allow retries */
	if (err)
		atomic_dec(cell->usage_count);

	return err;
}