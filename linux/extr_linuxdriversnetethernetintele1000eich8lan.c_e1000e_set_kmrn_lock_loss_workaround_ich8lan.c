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
struct TYPE_4__ {scalar_t__ type; } ;
struct e1000_dev_spec_ich8lan {int kmrn_lock_loss_workaround_enabled; } ;
struct TYPE_3__ {struct e1000_dev_spec_ich8lan ich8lan; } ;
struct e1000_hw {TYPE_2__ mac; TYPE_1__ dev_spec; } ;

/* Variables and functions */
 scalar_t__ e1000_ich8lan ; 
 int /*<<< orphan*/  e_dbg (char*) ; 

void e1000e_set_kmrn_lock_loss_workaround_ich8lan(struct e1000_hw *hw,
						  bool state)
{
	struct e1000_dev_spec_ich8lan *dev_spec = &hw->dev_spec.ich8lan;

	if (hw->mac.type != e1000_ich8lan) {
		e_dbg("Workaround applies to ICH8 only.\n");
		return;
	}

	dev_spec->kmrn_lock_loss_workaround_enabled = state;
}