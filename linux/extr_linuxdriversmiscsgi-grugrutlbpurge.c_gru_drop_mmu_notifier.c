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
struct gru_mm_struct {int /*<<< orphan*/  ms_notifier; int /*<<< orphan*/  ms_released; int /*<<< orphan*/  ms_refcnt; } ;
struct TYPE_2__ {int /*<<< orphan*/  mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  STAT (int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_dec_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  gms_free ; 
 int /*<<< orphan*/  gru_dbg (int /*<<< orphan*/ ,char*,struct gru_mm_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grudev ; 
 int /*<<< orphan*/  kfree (struct gru_mm_struct*) ; 
 int /*<<< orphan*/  mmu_notifier_unregister (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void gru_drop_mmu_notifier(struct gru_mm_struct *gms)
{
	gru_dbg(grudev, "gms %p, refcnt %d, released %d\n", gms,
		atomic_read(&gms->ms_refcnt), gms->ms_released);
	if (atomic_dec_return(&gms->ms_refcnt) == 0) {
		if (!gms->ms_released)
			mmu_notifier_unregister(&gms->ms_notifier, current->mm);
		kfree(gms);
		STAT(gms_free);
	}
}