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
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  gmap_asce; int /*<<< orphan*/  gmap_list; } ;
struct mm_struct {TYPE_1__ context; } ;
struct gmap {unsigned long asce; int /*<<< orphan*/  list; struct mm_struct* mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,unsigned long) ; 
 struct gmap* gmap_alloc (unsigned long) ; 
 int /*<<< orphan*/  list_add_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_is_singular (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

struct gmap *gmap_create(struct mm_struct *mm, unsigned long limit)
{
	struct gmap *gmap;
	unsigned long gmap_asce;

	gmap = gmap_alloc(limit);
	if (!gmap)
		return NULL;
	gmap->mm = mm;
	spin_lock(&mm->context.lock);
	list_add_rcu(&gmap->list, &mm->context.gmap_list);
	if (list_is_singular(&mm->context.gmap_list))
		gmap_asce = gmap->asce;
	else
		gmap_asce = -1UL;
	WRITE_ONCE(mm->context.gmap_asce, gmap_asce);
	spin_unlock(&mm->context.lock);
	return gmap;
}