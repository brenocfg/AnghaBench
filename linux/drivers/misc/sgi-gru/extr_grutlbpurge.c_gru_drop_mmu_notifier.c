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
struct gru_mm_struct {int /*<<< orphan*/  ms_notifier; } ;

/* Variables and functions */
 int /*<<< orphan*/  mmu_notifier_put (int /*<<< orphan*/ *) ; 

void gru_drop_mmu_notifier(struct gru_mm_struct *gms)
{
	mmu_notifier_put(&gms->ms_notifier);
}