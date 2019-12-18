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
typedef  int /*<<< orphan*/  u16 ;
struct hinic_api_cmd_chain {scalar_t__ chain_type; } ;
typedef  enum hinic_node_id { ____Placeholder_hinic_node_id } hinic_node_id ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ HINIC_API_CMD_WRITE_TO_MGMT_CPU ; 
 int api_cmd (struct hinic_api_cmd_chain*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int hinic_api_cmd_write(struct hinic_api_cmd_chain *chain,
			enum hinic_node_id dest, u8 *cmd, u16 size)
{
	/* Verify the chain type */
	if (chain->chain_type == HINIC_API_CMD_WRITE_TO_MGMT_CPU)
		return api_cmd(chain, dest, cmd, size);

	return -EINVAL;
}