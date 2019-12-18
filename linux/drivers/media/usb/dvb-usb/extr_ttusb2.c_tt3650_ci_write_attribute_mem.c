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
typedef  int u8 ;
struct dvb_ca_en50221 {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  TT3650_CMD_CI_WR_ATTR ; 
 int /*<<< orphan*/  ci_dbg (char*,int,int,int) ; 
 int tt3650_ci_msg_locked (struct dvb_ca_en50221*,int /*<<< orphan*/ ,int*,int,int) ; 

__attribute__((used)) static int tt3650_ci_write_attribute_mem(struct dvb_ca_en50221 *ca, int slot, int address, u8 value)
{
	u8 buf[3];

	ci_dbg("%d 0x%04x 0x%02x", slot, address, value);

	if (slot)
		return -EINVAL;

	buf[0] = (address >> 8) & 0x0F;
	buf[1] = address;
	buf[2] = value;

	return tt3650_ci_msg_locked(ca, TT3650_CMD_CI_WR_ATTR, buf, 3, 3);
}