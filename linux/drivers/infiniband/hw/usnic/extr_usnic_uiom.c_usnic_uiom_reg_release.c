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
struct usnic_uiom_reg {TYPE_1__* owning_mm; int /*<<< orphan*/  pd; } ;
struct TYPE_2__ {int /*<<< orphan*/  pinned_vm; } ;

/* Variables and functions */
 int /*<<< orphan*/  __usnic_uiom_reg_release (int /*<<< orphan*/ ,struct usnic_uiom_reg*,int) ; 
 int /*<<< orphan*/  __usnic_uiom_release_tail (struct usnic_uiom_reg*) ; 
 int /*<<< orphan*/  atomic64_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usnic_uiom_num_pages (struct usnic_uiom_reg*) ; 

void usnic_uiom_reg_release(struct usnic_uiom_reg *uiomr)
{
	__usnic_uiom_reg_release(uiomr->pd, uiomr, 1);

	atomic64_sub(usnic_uiom_num_pages(uiomr), &uiomr->owning_mm->pinned_vm);
	__usnic_uiom_release_tail(uiomr);
}