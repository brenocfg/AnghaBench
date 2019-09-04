#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int (* get_fault ) (struct fm10k_hw*,int,struct fm10k_fault*) ;} ;
struct TYPE_5__ {TYPE_1__ ops; } ;
struct fm10k_hw {TYPE_2__ mac; } ;
struct fm10k_intfc {TYPE_3__* pdev; struct fm10k_hw hw; } ;
struct fm10k_fault {int /*<<< orphan*/  member_0; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int FM10K_EICR_FAULT_MASK ; 
 scalar_t__ FM10K_FAULT_SIZE ; 
 int FM10K_PCA_FAULT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fm10k_handle_fault (struct fm10k_intfc*,int,struct fm10k_fault*) ; 
 int stub1 (struct fm10k_hw*,int,struct fm10k_fault*) ; 

__attribute__((used)) static void fm10k_report_fault(struct fm10k_intfc *interface, u32 eicr)
{
	struct fm10k_hw *hw = &interface->hw;
	struct fm10k_fault fault = { 0 };
	int type, err;

	for (eicr &= FM10K_EICR_FAULT_MASK, type = FM10K_PCA_FAULT;
	     eicr;
	     eicr >>= 1, type += FM10K_FAULT_SIZE) {
		/* only check if there is an error reported */
		if (!(eicr & 0x1))
			continue;

		/* retrieve fault info */
		err = hw->mac.ops.get_fault(hw, type, &fault);
		if (err) {
			dev_err(&interface->pdev->dev,
				"error reading fault\n");
			continue;
		}

		fm10k_handle_fault(interface, type, &fault);
	}
}