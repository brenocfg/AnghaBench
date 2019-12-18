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
typedef  int u32 ;
struct ipw2100_priv {int rts_threshold; } ;
struct host_command {int host_command_length; int* host_command_parameters; int /*<<< orphan*/  host_command_sequence; int /*<<< orphan*/  host_command; } ;

/* Variables and functions */
 int MAX_RTS_THRESHOLD ; 
 int RTS_DISABLED ; 
 int /*<<< orphan*/  RTS_THRESHOLD ; 
 int ipw2100_hw_send_command (struct ipw2100_priv*,struct host_command*) ; 

__attribute__((used)) static int ipw2100_set_rts_threshold(struct ipw2100_priv *priv, u32 threshold)
{
	struct host_command cmd = {
		.host_command = RTS_THRESHOLD,
		.host_command_sequence = 0,
		.host_command_length = 4
	};
	int err;

	if (threshold & RTS_DISABLED)
		cmd.host_command_parameters[0] = MAX_RTS_THRESHOLD;
	else
		cmd.host_command_parameters[0] = threshold & ~RTS_DISABLED;

	err = ipw2100_hw_send_command(priv, &cmd);
	if (err)
		return err;

	priv->rts_threshold = threshold;

	return 0;
}