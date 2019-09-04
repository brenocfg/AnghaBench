#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  (* setup_link ) (TYPE_5__*) ;} ;
struct TYPE_10__ {TYPE_3__ ops; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* power_up ) (TYPE_5__*) ;} ;
struct TYPE_8__ {TYPE_1__ ops; } ;
struct TYPE_11__ {TYPE_4__ mac; TYPE_2__ phy; } ;
struct e1000_adapter {TYPE_5__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_5__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_5__*) ; 

void e1000e_power_up_phy(struct e1000_adapter *adapter)
{
	if (adapter->hw.phy.ops.power_up)
		adapter->hw.phy.ops.power_up(&adapter->hw);

	adapter->hw.mac.ops.setup_link(&adapter->hw);
}