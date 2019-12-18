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
struct usnic_uiom_reg {int /*<<< orphan*/  owning_mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct usnic_uiom_reg*) ; 
 int /*<<< orphan*/  mmdrop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __usnic_uiom_release_tail(struct usnic_uiom_reg *uiomr)
{
	mmdrop(uiomr->owning_mm);
	kfree(uiomr);
}