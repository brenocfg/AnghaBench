#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  init_params; } ;
struct TYPE_8__ {TYPE_3__ ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  init_params; } ;
struct TYPE_6__ {TYPE_1__ ops; } ;
struct e1000_hw {TYPE_4__ mbx; TYPE_2__ mac; } ;

/* Variables and functions */
 int /*<<< orphan*/  e1000_init_mac_params_vf ; 
 int /*<<< orphan*/  e1000_init_mbx_params_vf ; 

void e1000_init_function_pointers_vf(struct e1000_hw *hw)
{
	hw->mac.ops.init_params = e1000_init_mac_params_vf;
	hw->mbx.ops.init_params = e1000_init_mbx_params_vf;
}