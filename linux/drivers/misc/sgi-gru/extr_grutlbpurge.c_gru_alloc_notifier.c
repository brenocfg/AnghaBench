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
struct mmu_notifier {int dummy; } ;
struct mm_struct {int dummy; } ;
struct gru_mm_struct {struct mmu_notifier ms_notifier; int /*<<< orphan*/  ms_wait_queue; int /*<<< orphan*/  ms_asid_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct mmu_notifier* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  STAT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gms_alloc ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct gru_mm_struct* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct mmu_notifier *gru_alloc_notifier(struct mm_struct *mm)
{
	struct gru_mm_struct *gms;

	gms = kzalloc(sizeof(*gms), GFP_KERNEL);
	if (!gms)
		return ERR_PTR(-ENOMEM);
	STAT(gms_alloc);
	spin_lock_init(&gms->ms_asid_lock);
	init_waitqueue_head(&gms->ms_wait_queue);

	return &gms->ms_notifier;
}