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
typedef  int /*<<< orphan*/  u32 ;
struct usb_serial_port {int dummy; } ;
typedef  int /*<<< orphan*/  le32_val ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int cp210x_write_reg_block (struct usb_serial_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cp210x_write_u32_reg(struct usb_serial_port *port, u8 req, u32 val)
{
	__le32 le32_val;

	le32_val = cpu_to_le32(val);

	return cp210x_write_reg_block(port, req, &le32_val, sizeof(le32_val));
}