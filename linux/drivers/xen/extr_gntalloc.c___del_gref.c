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
typedef  scalar_t__ uint8_t ;
struct TYPE_2__ {int flags; size_t pgoff; int /*<<< orphan*/  event; } ;
struct gntalloc_gref {scalar_t__ page; int /*<<< orphan*/  next_gref; scalar_t__ gref_id; TYPE_1__ notify; } ;

/* Variables and functions */
 int UNMAP_NOTIFY_CLEAR_BYTE ; 
 int UNMAP_NOTIFY_SEND_EVENT ; 
 int /*<<< orphan*/  __free_page (scalar_t__) ; 
 int /*<<< orphan*/  evtchn_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gnttab_end_foreign_access_ref (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gnttab_free_grant_reference (scalar_t__) ; 
 scalar_t__ gnttab_query_foreign_access (scalar_t__) ; 
 int /*<<< orphan*/  gref_size ; 
 int /*<<< orphan*/  kfree (struct gntalloc_gref*) ; 
 scalar_t__* kmap (scalar_t__) ; 
 int /*<<< orphan*/  kunmap (scalar_t__) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  notify_remote_via_evtchn (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __del_gref(struct gntalloc_gref *gref)
{
	if (gref->notify.flags & UNMAP_NOTIFY_CLEAR_BYTE) {
		uint8_t *tmp = kmap(gref->page);
		tmp[gref->notify.pgoff] = 0;
		kunmap(gref->page);
	}
	if (gref->notify.flags & UNMAP_NOTIFY_SEND_EVENT) {
		notify_remote_via_evtchn(gref->notify.event);
		evtchn_put(gref->notify.event);
	}

	gref->notify.flags = 0;

	if (gref->gref_id) {
		if (gnttab_query_foreign_access(gref->gref_id))
			return;

		if (!gnttab_end_foreign_access_ref(gref->gref_id, 0))
			return;

		gnttab_free_grant_reference(gref->gref_id);
	}

	gref_size--;
	list_del(&gref->next_gref);

	if (gref->page)
		__free_page(gref->page);

	kfree(gref);
}