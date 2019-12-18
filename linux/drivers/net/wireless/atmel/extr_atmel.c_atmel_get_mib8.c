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
typedef  void* u8 ;
struct get_set_mib {int size; void* index; void* type; } ;
struct atmel_private {int dummy; } ;

/* Variables and functions */
 scalar_t__ CMD_BLOCK_PARAMETERS_OFFSET ; 
 int /*<<< orphan*/  CMD_Get_MIB_Vars ; 
 scalar_t__ MIB_HEADER_SIZE ; 
 int /*<<< orphan*/  atmel_co (struct atmel_private*,scalar_t__) ; 
 void* atmel_rmem8 (struct atmel_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atmel_send_command_wait (struct atmel_private*,int /*<<< orphan*/ ,struct get_set_mib*,scalar_t__) ; 

__attribute__((used)) static u8 atmel_get_mib8(struct atmel_private *priv, u8 type, u8 index)
{
	struct get_set_mib m;
	m.type = type;
	m.size = 1;
	m.index = index;

	atmel_send_command_wait(priv, CMD_Get_MIB_Vars, &m, MIB_HEADER_SIZE + 1);
	return atmel_rmem8(priv, atmel_co(priv, CMD_BLOCK_PARAMETERS_OFFSET + MIB_HEADER_SIZE));
}