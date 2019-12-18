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
struct usb_serial_port {int dummy; } ;
typedef  int /*<<< orphan*/  le16_val ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int cp210x_read_reg_block (struct usb_serial_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cp210x_read_u16_reg(struct usb_serial_port *port, u8 req, u16 *val)
{
	__le16 le16_val;
	int err;

	err = cp210x_read_reg_block(port, req, &le16_val, sizeof(le16_val));
	if (err)
		return err;

	*val = le16_to_cpu(le16_val);

	return 0;
}