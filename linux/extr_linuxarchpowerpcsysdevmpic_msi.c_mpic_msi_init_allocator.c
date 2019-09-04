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
struct mpic {int flags; int /*<<< orphan*/  msi_bitmap; int /*<<< orphan*/  irqhost; int /*<<< orphan*/  num_sources; } ;

/* Variables and functions */
 int MPIC_U3_HT_IRQS ; 
 int /*<<< orphan*/  irq_domain_get_of_node (int /*<<< orphan*/ ) ; 
 int mpic_msi_reserve_u3_hwirqs (struct mpic*) ; 
 int msi_bitmap_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msi_bitmap_free (int /*<<< orphan*/ *) ; 
 int msi_bitmap_reserve_dt_hwirqs (int /*<<< orphan*/ *) ; 

int mpic_msi_init_allocator(struct mpic *mpic)
{
	int rc;

	rc = msi_bitmap_alloc(&mpic->msi_bitmap, mpic->num_sources,
			      irq_domain_get_of_node(mpic->irqhost));
	if (rc)
		return rc;

	rc = msi_bitmap_reserve_dt_hwirqs(&mpic->msi_bitmap);
	if (rc > 0) {
		if (mpic->flags & MPIC_U3_HT_IRQS)
			rc = mpic_msi_reserve_u3_hwirqs(mpic);

		if (rc) {
			msi_bitmap_free(&mpic->msi_bitmap);
			return rc;
		}
	}

	return 0;
}