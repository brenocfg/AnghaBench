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
struct gntab_unmap_queue_data {scalar_t__ age; int /*<<< orphan*/  gnttab_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __gnttab_unmap_refs_async (struct gntab_unmap_queue_data*) ; 
 int /*<<< orphan*/  gnttab_unmap_work ; 

void gnttab_unmap_refs_async(struct gntab_unmap_queue_data* item)
{
	INIT_DELAYED_WORK(&item->gnttab_work, gnttab_unmap_work);
	item->age = 0;

	__gnttab_unmap_refs_async(item);
}