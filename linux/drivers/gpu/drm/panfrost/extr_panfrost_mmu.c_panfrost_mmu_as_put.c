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
struct panfrost_mmu {int /*<<< orphan*/  as_count; } ;
struct panfrost_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 

void panfrost_mmu_as_put(struct panfrost_device *pfdev, struct panfrost_mmu *mmu)
{
	atomic_dec(&mmu->as_count);
	WARN_ON(atomic_read(&mmu->as_count) < 0);
}