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
struct intel_vgpu_i2c_edid {scalar_t__ state; scalar_t__ current_edid_read; int /*<<< orphan*/  port; int /*<<< orphan*/  edid_available; int /*<<< orphan*/  slave_selected; } ;
struct intel_vgpu_edid_data {unsigned char* edid_block; } ;
struct TYPE_3__ {struct intel_vgpu_i2c_edid i2c_edid; } ;
struct intel_vgpu {TYPE_1__ display; } ;
struct TYPE_4__ {struct intel_vgpu_edid_data* edid; } ;

/* Variables and functions */
 scalar_t__ EDID_SIZE ; 
 scalar_t__ I2C_NOT_SPECIFIED ; 
 int /*<<< orphan*/  gvt_vgpu_err (char*) ; 
 scalar_t__ intel_vgpu_has_monitor_on_port (struct intel_vgpu*,int /*<<< orphan*/ ) ; 
 TYPE_2__* intel_vgpu_port (struct intel_vgpu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned char edid_get_byte(struct intel_vgpu *vgpu)
{
	struct intel_vgpu_i2c_edid *edid = &vgpu->display.i2c_edid;
	unsigned char chr = 0;

	if (edid->state == I2C_NOT_SPECIFIED || !edid->slave_selected) {
		gvt_vgpu_err("Driver tries to read EDID without proper sequence!\n");
		return 0;
	}
	if (edid->current_edid_read >= EDID_SIZE) {
		gvt_vgpu_err("edid_get_byte() exceeds the size of EDID!\n");
		return 0;
	}

	if (!edid->edid_available) {
		gvt_vgpu_err("Reading EDID but EDID is not available!\n");
		return 0;
	}

	if (intel_vgpu_has_monitor_on_port(vgpu, edid->port)) {
		struct intel_vgpu_edid_data *edid_data =
			intel_vgpu_port(vgpu, edid->port)->edid;

		chr = edid_data->edid_block[edid->current_edid_read];
		edid->current_edid_read++;
	} else {
		gvt_vgpu_err("No EDID available during the reading?\n");
	}
	return chr;
}