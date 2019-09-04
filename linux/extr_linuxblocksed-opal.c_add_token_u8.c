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
struct opal_dev {int pos; int /*<<< orphan*/ * cmd; } ;

/* Variables and functions */
 int ERANGE ; 
 int IO_BUFFER_LENGTH ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

__attribute__((used)) static void add_token_u8(int *err, struct opal_dev *cmd, u8 tok)
{
	if (*err)
		return;
	if (cmd->pos >= IO_BUFFER_LENGTH - 1) {
		pr_debug("Error adding u8: end of buffer.\n");
		*err = -ERANGE;
		return;
	}
	cmd->cmd[cmd->pos++] = tok;
}