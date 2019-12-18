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
struct radeon_mn {struct mmu_notifier mn; int /*<<< orphan*/  objects; int /*<<< orphan*/  lock; } ;
struct mm_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct mmu_notifier* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  RB_ROOT_CACHED ; 
 struct radeon_mn* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct mmu_notifier *radeon_mn_alloc_notifier(struct mm_struct *mm)
{
	struct radeon_mn *rmn;

	rmn = kzalloc(sizeof(*rmn), GFP_KERNEL);
	if (!rmn)
		return ERR_PTR(-ENOMEM);

	mutex_init(&rmn->lock);
	rmn->objects = RB_ROOT_CACHED;
	return &rmn->mn;
}