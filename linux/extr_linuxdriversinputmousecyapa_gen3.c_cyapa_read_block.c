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
typedef  size_t u8 ;
struct cyapa {scalar_t__ smbus; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_4__ {size_t cmd; size_t len; } ;
struct TYPE_3__ {size_t cmd; size_t len; } ;

/* Variables and functions */
 TYPE_2__* cyapa_i2c_cmds ; 
 int /*<<< orphan*/  cyapa_i2c_reg_read_block (struct cyapa*,size_t,size_t,size_t*) ; 
 TYPE_1__* cyapa_smbus_cmds ; 
 int /*<<< orphan*/  cyapa_smbus_read_block (struct cyapa*,size_t,size_t,size_t*) ; 

ssize_t cyapa_read_block(struct cyapa *cyapa, u8 cmd_idx, u8 *values)
{
	u8 cmd;
	size_t len;

	if (cyapa->smbus) {
		cmd = cyapa_smbus_cmds[cmd_idx].cmd;
		len = cyapa_smbus_cmds[cmd_idx].len;
		return cyapa_smbus_read_block(cyapa, cmd, len, values);
	}
	cmd = cyapa_i2c_cmds[cmd_idx].cmd;
	len = cyapa_i2c_cmds[cmd_idx].len;
	return cyapa_i2c_reg_read_block(cyapa, cmd, len, values);
}