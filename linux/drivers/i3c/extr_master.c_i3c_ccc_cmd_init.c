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
struct i3c_ccc_cmd_dest {int dummy; } ;
struct i3c_ccc_cmd {int rnw; unsigned int ndests; int /*<<< orphan*/  err; struct i3c_ccc_cmd_dest* dests; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  I3C_ERROR_UNKNOWN ; 

__attribute__((used)) static void i3c_ccc_cmd_init(struct i3c_ccc_cmd *cmd, bool rnw, u8 id,
			     struct i3c_ccc_cmd_dest *dests,
			     unsigned int ndests)
{
	cmd->rnw = rnw ? 1 : 0;
	cmd->id = id;
	cmd->dests = dests;
	cmd->ndests = ndests;
	cmd->err = I3C_ERROR_UNKNOWN;
}