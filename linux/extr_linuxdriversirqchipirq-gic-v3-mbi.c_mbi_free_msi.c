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
struct mbi_range {scalar_t__ spi_start; int /*<<< orphan*/  bm; } ;

/* Variables and functions */
 int /*<<< orphan*/  bitmap_release_region (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_count_order (int) ; 
 int /*<<< orphan*/  mbi_lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mbi_free_msi(struct mbi_range *mbi, unsigned int hwirq,
			 int nr_irqs)
{
	mutex_lock(&mbi_lock);
	bitmap_release_region(mbi->bm, hwirq - mbi->spi_start,
			      get_count_order(nr_irqs));
	mutex_unlock(&mbi_lock);
}