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
struct opal_dev {int* cmd; int /*<<< orphan*/  pos; } ;

/* Variables and functions */
 int MEDIUM_ATOM_BYTESTRING ; 
 int MEDIUM_ATOM_ID ; 
 int MEDIUM_ATOM_LEN_MASK ; 
 int MEDIUM_ATOM_SIGNED ; 

__attribute__((used)) static void add_medium_atom_header(struct opal_dev *cmd, bool bytestring,
				   bool has_sign, int len)
{
	u8 header0;

	header0 = MEDIUM_ATOM_ID;
	header0 |= bytestring ? MEDIUM_ATOM_BYTESTRING : 0;
	header0 |= has_sign ? MEDIUM_ATOM_SIGNED : 0;
	header0 |= (len >> 8) & MEDIUM_ATOM_LEN_MASK;
	cmd->cmd[cmd->pos++] = header0;
	cmd->cmd[cmd->pos++] = len;
}