#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int max_port_number; } ;
struct tb_switch {int /*<<< orphan*/  dev; scalar_t__ rpm; scalar_t__ device_name; scalar_t__ vendor_name; scalar_t__ device; scalar_t__ vendor; TYPE_2__* ports; TYPE_1__ config; int /*<<< orphan*/  uid; int /*<<< orphan*/  safe_mode; } ;
struct TYPE_5__ {scalar_t__ disabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  TB_AUTOSUSPEND_DELAY ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,scalar_t__,scalar_t__) ; 
 int device_add (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_request_autosuspend (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_set_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (int /*<<< orphan*/ *) ; 
 int tb_drom_read (struct tb_switch*) ; 
 int tb_init_port (TYPE_2__*) ; 
 int /*<<< orphan*/  tb_port_dbg (TYPE_2__*,char*) ; 
 scalar_t__ tb_route (struct tb_switch*) ; 
 int /*<<< orphan*/  tb_sw_dbg (struct tb_switch*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tb_sw_warn (struct tb_switch*,char*) ; 
 int tb_switch_add_dma_port (struct tb_switch*) ; 
 int tb_switch_nvm_add (struct tb_switch*) ; 
 int tb_switch_set_uuid (struct tb_switch*) ; 

int tb_switch_add(struct tb_switch *sw)
{
	int i, ret;

	/*
	 * Initialize DMA control port now before we read DROM. Recent
	 * host controllers have more complete DROM on NVM that includes
	 * vendor and model identification strings which we then expose
	 * to the userspace. NVM can be accessed through DMA
	 * configuration based mailbox.
	 */
	ret = tb_switch_add_dma_port(sw);
	if (ret)
		return ret;

	if (!sw->safe_mode) {
		/* read drom */
		ret = tb_drom_read(sw);
		if (ret) {
			tb_sw_warn(sw, "tb_eeprom_read_rom failed\n");
			return ret;
		}
		tb_sw_dbg(sw, "uid: %#llx\n", sw->uid);

		ret = tb_switch_set_uuid(sw);
		if (ret)
			return ret;

		for (i = 0; i <= sw->config.max_port_number; i++) {
			if (sw->ports[i].disabled) {
				tb_port_dbg(&sw->ports[i], "disabled by eeprom\n");
				continue;
			}
			ret = tb_init_port(&sw->ports[i]);
			if (ret)
				return ret;
		}
	}

	ret = device_add(&sw->dev);
	if (ret)
		return ret;

	if (tb_route(sw)) {
		dev_info(&sw->dev, "new device found, vendor=%#x device=%#x\n",
			 sw->vendor, sw->device);
		if (sw->vendor_name && sw->device_name)
			dev_info(&sw->dev, "%s %s\n", sw->vendor_name,
				 sw->device_name);
	}

	ret = tb_switch_nvm_add(sw);
	if (ret) {
		device_del(&sw->dev);
		return ret;
	}

	pm_runtime_set_active(&sw->dev);
	if (sw->rpm) {
		pm_runtime_set_autosuspend_delay(&sw->dev, TB_AUTOSUSPEND_DELAY);
		pm_runtime_use_autosuspend(&sw->dev);
		pm_runtime_mark_last_busy(&sw->dev);
		pm_runtime_enable(&sw->dev);
		pm_request_autosuspend(&sw->dev);
	}

	return 0;
}