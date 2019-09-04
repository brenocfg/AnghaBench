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
struct cyapa {int /*<<< orphan*/  client; scalar_t__ smbus; } ;
typedef  int /*<<< orphan*/  s32 ;
struct TYPE_4__ {size_t cmd; } ;
struct TYPE_3__ {size_t cmd; } ;

/* Variables and functions */
 size_t SMBUS_ENCODE_RW (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMBUS_WRITE ; 
 TYPE_2__* cyapa_i2c_cmds ; 
 TYPE_1__* cyapa_smbus_cmds ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (int /*<<< orphan*/ ,size_t,size_t) ; 

__attribute__((used)) static s32 cyapa_write_byte(struct cyapa *cyapa, u8 cmd_idx, u8 value)
{
	u8 cmd;

	if (cyapa->smbus) {
		cmd = cyapa_smbus_cmds[cmd_idx].cmd;
		cmd = SMBUS_ENCODE_RW(cmd, SMBUS_WRITE);
	} else {
		cmd = cyapa_i2c_cmds[cmd_idx].cmd;
	}
	return i2c_smbus_write_byte_data(cyapa->client, cmd, value);
}