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
struct TYPE_2__ {scalar_t__ type; } ;
struct fm10k_hw {TYPE_1__ mac; } ;
struct fm10k_intfc {scalar_t__ host_ready; struct fm10k_hw hw; } ;

/* Variables and functions */
 scalar_t__ fm10k_mac_vf ; 

__attribute__((used)) static bool fm10k_host_mbx_ready(struct fm10k_intfc *interface)
{
	struct fm10k_hw *hw = &interface->hw;

	return (hw->mac.type == fm10k_mac_vf || interface->host_ready);
}