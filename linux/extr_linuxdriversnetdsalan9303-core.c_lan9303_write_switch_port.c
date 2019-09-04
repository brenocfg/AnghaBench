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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct lan9303 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LAN9303_SWITCH_PORT_REG (int,int /*<<< orphan*/ ) ; 
 int lan9303_write_switch_reg (struct lan9303*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lan9303_write_switch_port(struct lan9303 *chip, int port,
				     u16 regnum, u32 val)
{
	return lan9303_write_switch_reg(
		chip, LAN9303_SWITCH_PORT_REG(port, regnum), val);
}