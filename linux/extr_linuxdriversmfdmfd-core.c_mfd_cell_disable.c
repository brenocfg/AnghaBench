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
struct mfd_cell {int (* disable ) (struct platform_device*) ;int /*<<< orphan*/  usage_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ atomic_dec_return (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ ) ; 
 struct mfd_cell* mfd_get_cell (struct platform_device*) ; 
 int stub1 (struct platform_device*) ; 

int mfd_cell_disable(struct platform_device *pdev)
{
	const struct mfd_cell *cell = mfd_get_cell(pdev);
	int err = 0;

	/* only disable if no other clients are using it */
	if (atomic_dec_return(cell->usage_count) == 0)
		err = cell->disable(pdev);

	/* if the disable hook failed, increment to allow retries */
	if (err)
		atomic_inc(cell->usage_count);

	/* sanity check; did someone call disable too many times? */
	WARN_ON(atomic_read(cell->usage_count) < 0);

	return err;
}