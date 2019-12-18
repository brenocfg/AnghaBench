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
struct hfi1_devdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_FIRST_SOURCE ; 
 int /*<<< orphan*/  IS_LAST_SOURCE ; 
 int /*<<< orphan*/  clear_all_interrupts (struct hfi1_devdata*) ; 
 int /*<<< orphan*/  msix_clean_up_interrupts (struct hfi1_devdata*) ; 
 int msix_initialize (struct hfi1_devdata*) ; 
 int msix_request_irqs (struct hfi1_devdata*) ; 
 int /*<<< orphan*/  reset_interrupts (struct hfi1_devdata*) ; 
 int /*<<< orphan*/  set_intr_bits (struct hfi1_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int set_up_interrupts(struct hfi1_devdata *dd)
{
	int ret;

	/* mask all interrupts */
	set_intr_bits(dd, IS_FIRST_SOURCE, IS_LAST_SOURCE, false);

	/* clear all pending interrupts */
	clear_all_interrupts(dd);

	/* reset general handler mask, chip MSI-X mappings */
	reset_interrupts(dd);

	/* ask for MSI-X interrupts */
	ret = msix_initialize(dd);
	if (ret)
		return ret;

	ret = msix_request_irqs(dd);
	if (ret)
		msix_clean_up_interrupts(dd);

	return ret;
}