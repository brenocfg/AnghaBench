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
struct TYPE_2__ {int /*<<< orphan*/  alloc; } ;
struct mthca_dev {TYPE_1__ uar_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  mthca_alloc_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mthca_cleanup_db_tab (struct mthca_dev*) ; 

void mthca_cleanup_uar_table(struct mthca_dev *dev)
{
	mthca_cleanup_db_tab(dev);

	/* XXX check if any UARs are still allocated? */
	mthca_alloc_cleanup(&dev->uar_table.alloc);
}