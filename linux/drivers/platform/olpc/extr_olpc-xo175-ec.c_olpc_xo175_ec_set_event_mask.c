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
typedef  unsigned int u8 ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_WRITE_EXT_SCI_MASK ; 
 int olpc_ec_cmd (int /*<<< orphan*/ ,unsigned int*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int olpc_xo175_ec_set_event_mask(unsigned int mask)
{
	u8 args[2];

	args[0] = mask >> 0;
	args[1] = mask >> 8;
	return olpc_ec_cmd(CMD_WRITE_EXT_SCI_MASK, args, 2, NULL, 0);
}