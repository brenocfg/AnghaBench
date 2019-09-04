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
struct ldc_channel {struct ldc_channel* mssbuf; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  hlist_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ldc_channel*) ; 
 int /*<<< orphan*/  ldc_iommu_release (struct ldc_channel*) ; 
 int /*<<< orphan*/  ldc_unbind (struct ldc_channel*) ; 

void ldc_free(struct ldc_channel *lp)
{
	ldc_unbind(lp);
	hlist_del(&lp->list);
	kfree(lp->mssbuf);
	ldc_iommu_release(lp);

	kfree(lp);
}