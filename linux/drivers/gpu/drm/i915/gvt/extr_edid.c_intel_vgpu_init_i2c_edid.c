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
struct intel_vgpu_i2c_gmbus {int dummy; } ;
struct TYPE_3__ {int i2c_over_aux_ch; int aux_ch_mot; } ;
struct intel_vgpu_i2c_edid {int port; int slave_selected; int edid_available; TYPE_1__ aux_ch; int /*<<< orphan*/  gmbus; scalar_t__ current_edid_read; int /*<<< orphan*/  state; } ;
struct TYPE_4__ {struct intel_vgpu_i2c_edid i2c_edid; } ;
struct intel_vgpu {TYPE_2__ display; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_NOT_SPECIFIED ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void intel_vgpu_init_i2c_edid(struct intel_vgpu *vgpu)
{
	struct intel_vgpu_i2c_edid *edid = &vgpu->display.i2c_edid;

	edid->state = I2C_NOT_SPECIFIED;

	edid->port = -1;
	edid->slave_selected = false;
	edid->edid_available = false;
	edid->current_edid_read = 0;

	memset(&edid->gmbus, 0, sizeof(struct intel_vgpu_i2c_gmbus));

	edid->aux_ch.i2c_over_aux_ch = false;
	edid->aux_ch.aux_ch_mot = false;
}