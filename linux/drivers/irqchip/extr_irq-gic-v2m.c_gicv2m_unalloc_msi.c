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
struct v2m_data {scalar_t__ spi_start; int /*<<< orphan*/  bm; } ;

/* Variables and functions */
 int /*<<< orphan*/  bitmap_release_region (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_count_order (int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v2m_lock ; 

__attribute__((used)) static void gicv2m_unalloc_msi(struct v2m_data *v2m, unsigned int hwirq,
			       int nr_irqs)
{
	spin_lock(&v2m_lock);
	bitmap_release_region(v2m->bm, hwirq - v2m->spi_start,
			      get_count_order(nr_irqs));
	spin_unlock(&v2m_lock);
}