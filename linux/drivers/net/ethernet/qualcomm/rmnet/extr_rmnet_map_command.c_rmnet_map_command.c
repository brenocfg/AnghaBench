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
struct sk_buff {int dummy; } ;
struct rmnet_port {int dummy; } ;
struct rmnet_map_control_command {unsigned char command_name; } ;

/* Variables and functions */
 unsigned char RMNET_MAP_COMMAND_ACK ; 
#define  RMNET_MAP_COMMAND_FLOW_DISABLE 129 
#define  RMNET_MAP_COMMAND_FLOW_ENABLE 128 
 unsigned char RMNET_MAP_COMMAND_UNSUPPORTED ; 
 struct rmnet_map_control_command* RMNET_MAP_GET_CMD_START (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 unsigned char rmnet_map_do_flow_control (struct sk_buff*,struct rmnet_port*,int) ; 
 int /*<<< orphan*/  rmnet_map_send_ack (struct sk_buff*,unsigned char,struct rmnet_port*) ; 

void rmnet_map_command(struct sk_buff *skb, struct rmnet_port *port)
{
	struct rmnet_map_control_command *cmd;
	unsigned char command_name;
	unsigned char rc = 0;

	cmd = RMNET_MAP_GET_CMD_START(skb);
	command_name = cmd->command_name;

	switch (command_name) {
	case RMNET_MAP_COMMAND_FLOW_ENABLE:
		rc = rmnet_map_do_flow_control(skb, port, 1);
		break;

	case RMNET_MAP_COMMAND_FLOW_DISABLE:
		rc = rmnet_map_do_flow_control(skb, port, 0);
		break;

	default:
		rc = RMNET_MAP_COMMAND_UNSUPPORTED;
		kfree_skb(skb);
		break;
	}
	if (rc == RMNET_MAP_COMMAND_ACK)
		rmnet_map_send_ack(skb, rc, port);
}