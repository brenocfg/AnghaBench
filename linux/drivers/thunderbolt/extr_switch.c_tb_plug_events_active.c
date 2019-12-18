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
typedef  int u32 ;
struct TYPE_2__ {int plug_events_delay; int device_id; int /*<<< orphan*/  enabled; } ;
struct tb_switch {int cap_plug_events; TYPE_1__ config; } ;

/* Variables and functions */
#define  PCI_DEVICE_ID_INTEL_EAGLE_RIDGE 130 
#define  PCI_DEVICE_ID_INTEL_LIGHT_RIDGE 129 
#define  PCI_DEVICE_ID_INTEL_PORT_RIDGE 128 
 int /*<<< orphan*/  TB_CFG_SWITCH ; 
 int tb_sw_read (struct tb_switch*,int*,int /*<<< orphan*/ ,int,int) ; 
 int tb_sw_write (struct tb_switch*,int*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int tb_plug_events_active(struct tb_switch *sw, bool active)
{
	u32 data;
	int res;

	if (!sw->config.enabled)
		return 0;

	sw->config.plug_events_delay = 0xff;
	res = tb_sw_write(sw, ((u32 *) &sw->config) + 4, TB_CFG_SWITCH, 4, 1);
	if (res)
		return res;

	res = tb_sw_read(sw, &data, TB_CFG_SWITCH, sw->cap_plug_events + 1, 1);
	if (res)
		return res;

	if (active) {
		data = data & 0xFFFFFF83;
		switch (sw->config.device_id) {
		case PCI_DEVICE_ID_INTEL_LIGHT_RIDGE:
		case PCI_DEVICE_ID_INTEL_EAGLE_RIDGE:
		case PCI_DEVICE_ID_INTEL_PORT_RIDGE:
			break;
		default:
			data |= 4;
		}
	} else {
		data = data | 0x7c;
	}
	return tb_sw_write(sw, &data, TB_CFG_SWITCH,
			   sw->cap_plug_events + 1, 1);
}