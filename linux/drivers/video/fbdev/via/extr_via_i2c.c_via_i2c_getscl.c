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
struct via_port_cfg {scalar_t__ type; int /*<<< orphan*/  ioport_index; int /*<<< orphan*/  io_port; } ;
struct TYPE_2__ {int /*<<< orphan*/  reg_lock; } ;

/* Variables and functions */
 scalar_t__ VIA_PORT_GPIO ; 
 TYPE_1__* i2c_vdev ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int via_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  via_write_reg_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int via_i2c_getscl(void *data)
{
	struct via_port_cfg *adap_data = data;
	unsigned long flags;
	int ret = 0;

	spin_lock_irqsave(&i2c_vdev->reg_lock, flags);
	if (adap_data->type == VIA_PORT_GPIO)
		via_write_reg_mask(adap_data->io_port, adap_data->ioport_index,
			0, 0x80);
	if (via_read_reg(adap_data->io_port, adap_data->ioport_index) & 0x08)
		ret = 1;
	spin_unlock_irqrestore(&i2c_vdev->reg_lock, flags);
	return ret;
}