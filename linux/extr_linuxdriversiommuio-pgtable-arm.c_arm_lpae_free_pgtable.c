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
struct io_pgtable {int dummy; } ;
struct arm_lpae_io_pgtable {int /*<<< orphan*/  pgd; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_LPAE_START_LVL (struct arm_lpae_io_pgtable*) ; 
 int /*<<< orphan*/  __arm_lpae_free_pgtable (struct arm_lpae_io_pgtable*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct arm_lpae_io_pgtable* io_pgtable_to_data (struct io_pgtable*) ; 
 int /*<<< orphan*/  kfree (struct arm_lpae_io_pgtable*) ; 

__attribute__((used)) static void arm_lpae_free_pgtable(struct io_pgtable *iop)
{
	struct arm_lpae_io_pgtable *data = io_pgtable_to_data(iop);

	__arm_lpae_free_pgtable(data, ARM_LPAE_START_LVL(data), data->pgd);
	kfree(data);
}