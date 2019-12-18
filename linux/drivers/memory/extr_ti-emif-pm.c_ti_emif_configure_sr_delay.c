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
struct TYPE_2__ {scalar_t__ ti_emif_base_addr_virt; } ;
struct ti_emif_data {TYPE_1__ pm_data; } ;

/* Variables and functions */
 scalar_t__ EMIF_POWER_MANAGEMENT_CONTROL ; 
 scalar_t__ EMIF_POWER_MANAGEMENT_CTRL_SHDW ; 
 int /*<<< orphan*/  EMIF_POWER_MGMT_WAIT_SELF_REFRESH_8192_CYCLES ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void ti_emif_configure_sr_delay(struct ti_emif_data *emif_data)
{
	writel(EMIF_POWER_MGMT_WAIT_SELF_REFRESH_8192_CYCLES,
	       (emif_data->pm_data.ti_emif_base_addr_virt +
		EMIF_POWER_MANAGEMENT_CONTROL));

	writel(EMIF_POWER_MGMT_WAIT_SELF_REFRESH_8192_CYCLES,
	       (emif_data->pm_data.ti_emif_base_addr_virt +
		EMIF_POWER_MANAGEMENT_CTRL_SHDW));
}