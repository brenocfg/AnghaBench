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
struct ipw2100_priv {int /*<<< orphan*/  wait_command_queue; int /*<<< orphan*/  status; } ;
struct ipw2100_cmd_header {size_t host_command_reg; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 size_t CARD_DISABLE ; 
 size_t HOST_COMPLETE ; 
 int /*<<< orphan*/  IPW_DEBUG_HC (char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  STATUS_CMD_ACTIVE ; 
 int /*<<< orphan*/  STATUS_ENABLED ; 
 int /*<<< orphan*/ * command_types ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void isr_rx_complete_command(struct ipw2100_priv *priv,
				    struct ipw2100_cmd_header *cmd)
{
#ifdef CONFIG_IPW2100_DEBUG
	if (cmd->host_command_reg < ARRAY_SIZE(command_types)) {
		IPW_DEBUG_HC("Command completed '%s (%d)'\n",
			     command_types[cmd->host_command_reg],
			     cmd->host_command_reg);
	}
#endif
	if (cmd->host_command_reg == HOST_COMPLETE)
		priv->status |= STATUS_ENABLED;

	if (cmd->host_command_reg == CARD_DISABLE)
		priv->status &= ~STATUS_ENABLED;

	priv->status &= ~STATUS_CMD_ACTIVE;

	wake_up_interruptible(&priv->wait_command_queue);
}