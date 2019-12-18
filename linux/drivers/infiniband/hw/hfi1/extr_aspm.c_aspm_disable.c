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
struct hfi1_devdata {int aspm_enabled; } ;

/* Variables and functions */
 scalar_t__ ASPM_MODE_ENABLED ; 
 int /*<<< orphan*/  aspm_hw_disable_l1 (struct hfi1_devdata*) ; 
 scalar_t__ aspm_mode ; 

__attribute__((used)) static  void aspm_disable(struct hfi1_devdata *dd)
{
	if (!dd->aspm_enabled || aspm_mode == ASPM_MODE_ENABLED)
		return;

	aspm_hw_disable_l1(dd);
	dd->aspm_enabled = false;
}