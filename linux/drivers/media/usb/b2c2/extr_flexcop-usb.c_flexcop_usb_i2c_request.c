#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct flexcop_i2c_adapter {int dummy; } ;
typedef  scalar_t__ flexcop_access_op_t ;

/* Variables and functions */
 int /*<<< orphan*/  B2C2_USB_I2C_REQUEST ; 
 scalar_t__ FC_READ ; 
 int /*<<< orphan*/  USB_FUNC_I2C_READ ; 
 int /*<<< orphan*/  USB_FUNC_I2C_WRITE ; 
 int flexcop_usb_i2c_req (struct flexcop_i2c_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int flexcop_usb_i2c_request(struct flexcop_i2c_adapter *i2c,
		flexcop_access_op_t op, u8 chipaddr, u8 addr, u8 *buf, u16 len)
{
	if (op == FC_READ)
		return flexcop_usb_i2c_req(i2c, B2C2_USB_I2C_REQUEST,
				USB_FUNC_I2C_READ, chipaddr, addr, buf, len);
	else
		return flexcop_usb_i2c_req(i2c, B2C2_USB_I2C_REQUEST,
				USB_FUNC_I2C_WRITE, chipaddr, addr, buf, len);
}