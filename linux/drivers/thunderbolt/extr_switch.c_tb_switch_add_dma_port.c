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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ enabled; } ;
struct tb_switch {int generation; int /*<<< orphan*/  dma_port; scalar_t__ no_nvm_upgrade; TYPE_1__ config; int /*<<< orphan*/  safe_mode; } ;

/* Variables and functions */
 int ESHUTDOWN ; 
 int /*<<< orphan*/  dma_port_alloc (struct tb_switch*) ; 
 int dma_port_flash_update_auth_status (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  dma_port_power_cycle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvm_authenticate_complete (struct tb_switch*) ; 
 int /*<<< orphan*/  nvm_set_auth_status (struct tb_switch*,scalar_t__) ; 
 scalar_t__ tb_route (struct tb_switch*) ; 
 int /*<<< orphan*/  tb_sw_info (struct tb_switch*,char*) ; 
 int tb_switch_set_uuid (struct tb_switch*) ; 

__attribute__((used)) static int tb_switch_add_dma_port(struct tb_switch *sw)
{
	u32 status;
	int ret;

	switch (sw->generation) {
	case 3:
		break;

	case 2:
		/* Only root switch can be upgraded */
		if (tb_route(sw))
			return 0;
		break;

	default:
		/*
		 * DMA port is the only thing available when the switch
		 * is in safe mode.
		 */
		if (!sw->safe_mode)
			return 0;
		break;
	}

	/* Root switch DMA port requires running firmware */
	if (!tb_route(sw) && sw->config.enabled)
		return 0;

	sw->dma_port = dma_port_alloc(sw);
	if (!sw->dma_port)
		return 0;

	if (sw->no_nvm_upgrade)
		return 0;

	/*
	 * Check status of the previous flash authentication. If there
	 * is one we need to power cycle the switch in any case to make
	 * it functional again.
	 */
	ret = dma_port_flash_update_auth_status(sw->dma_port, &status);
	if (ret <= 0)
		return ret;

	/* Now we can allow root port to suspend again */
	if (!tb_route(sw))
		nvm_authenticate_complete(sw);

	if (status) {
		tb_sw_info(sw, "switch flash authentication failed\n");
		ret = tb_switch_set_uuid(sw);
		if (ret)
			return ret;
		nvm_set_auth_status(sw, status);
	}

	tb_sw_info(sw, "power cycling the switch now\n");
	dma_port_power_cycle(sw->dma_port);

	/*
	 * We return error here which causes the switch adding failure.
	 * It should appear back after power cycle is complete.
	 */
	return -ESHUTDOWN;
}