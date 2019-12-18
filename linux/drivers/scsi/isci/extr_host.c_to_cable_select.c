#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned char cable_selection_mask; } ;
struct TYPE_4__ {TYPE_1__ controller; } ;
struct isci_host {int id; TYPE_2__ oem_parameters; } ;

/* Variables and functions */
 int /*<<< orphan*/  cable_selection_override ; 
 scalar_t__ is_cable_select_overridden () ; 

__attribute__((used)) static unsigned char *to_cable_select(struct isci_host *ihost)
{
	if (is_cable_select_overridden())
		return ((unsigned char *)&cable_selection_override)
			+ ihost->id;
	else
		return &ihost->oem_parameters.controller.cable_selection_mask;
}