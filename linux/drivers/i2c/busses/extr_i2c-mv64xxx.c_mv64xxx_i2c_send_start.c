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
struct TYPE_3__ {scalar_t__ control; } ;
struct mv64xxx_i2c_data {int cntl_bits; TYPE_1__ reg_offsets; scalar_t__ reg_base; TYPE_2__* msgs; scalar_t__ rc; scalar_t__ aborting; TYPE_2__* msg; int /*<<< orphan*/  bytes_left; scalar_t__ byte_posn; } ;
struct TYPE_4__ {int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int MV64XXX_I2C_REG_CONTROL_START ; 
 int /*<<< orphan*/  mv64xxx_i2c_prepare_for_io (struct mv64xxx_i2c_data*,TYPE_2__*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void mv64xxx_i2c_send_start(struct mv64xxx_i2c_data *drv_data)
{
	drv_data->msg = drv_data->msgs;
	drv_data->byte_posn = 0;
	drv_data->bytes_left = drv_data->msg->len;
	drv_data->aborting = 0;
	drv_data->rc = 0;

	mv64xxx_i2c_prepare_for_io(drv_data, drv_data->msgs);
	writel(drv_data->cntl_bits | MV64XXX_I2C_REG_CONTROL_START,
	       drv_data->reg_base + drv_data->reg_offsets.control);
}