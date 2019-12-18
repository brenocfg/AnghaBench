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
struct ocxl_link {int /*<<< orphan*/  irq_available; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pnv_ocxl_free_xive_irq (int) ; 

void ocxl_link_free_irq(void *link_handle, int hw_irq)
{
	struct ocxl_link *link = (struct ocxl_link *) link_handle;

	pnv_ocxl_free_xive_irq(hw_irq);
	atomic_inc(&link->irq_available);
}