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
struct fsl_msi {int /*<<< orphan*/  bitmap; int /*<<< orphan*/  irqhost; } ;

/* Variables and functions */
 int NR_MSI_IRQS_MAX ; 
 int /*<<< orphan*/  irq_domain_get_of_node (int /*<<< orphan*/ ) ; 
 int msi_bitmap_alloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msi_bitmap_reserve_hwirq (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int fsl_msi_init_allocator(struct fsl_msi *msi_data)
{
	int rc, hwirq;

	rc = msi_bitmap_alloc(&msi_data->bitmap, NR_MSI_IRQS_MAX,
			      irq_domain_get_of_node(msi_data->irqhost));
	if (rc)
		return rc;

	/*
	 * Reserve all the hwirqs
	 * The available hwirqs will be released in fsl_msi_setup_hwirq()
	 */
	for (hwirq = 0; hwirq < NR_MSI_IRQS_MAX; hwirq++)
		msi_bitmap_reserve_hwirq(&msi_data->bitmap, hwirq);

	return 0;
}