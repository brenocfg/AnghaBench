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
struct psb_mmu_pd {int dummy; } ;
struct psb_mmu_driver {int /*<<< orphan*/  sem; struct psb_mmu_pd* default_pd; } ;

/* Variables and functions */
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

struct psb_mmu_pd *psb_mmu_get_default_pd(struct psb_mmu_driver *driver)
{
	struct psb_mmu_pd *pd;

	down_read(&driver->sem);
	pd = driver->default_pd;
	up_read(&driver->sem);

	return pd;
}