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
struct pfn_array {int /*<<< orphan*/  pa_iova_pfn; scalar_t__ pa_nr; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfio_unpin_pages (struct device*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void pfn_array_unpin_free(struct pfn_array *pa, struct device *mdev)
{
	/* Only unpin if any pages were pinned to begin with */
	if (pa->pa_nr)
		vfio_unpin_pages(mdev, pa->pa_iova_pfn, pa->pa_nr);
	pa->pa_nr = 0;
	kfree(pa->pa_iova_pfn);
}