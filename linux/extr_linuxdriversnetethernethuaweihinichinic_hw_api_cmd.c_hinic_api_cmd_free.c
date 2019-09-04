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
struct hinic_api_cmd_chain {int dummy; } ;
typedef  enum hinic_api_cmd_chain_type { ____Placeholder_hinic_api_cmd_chain_type } hinic_api_cmd_chain_type ;

/* Variables and functions */
 int HINIC_API_CMD_MAX ; 
 int HINIC_API_CMD_WRITE_TO_MGMT_CPU ; 
 int /*<<< orphan*/  api_cmd_destroy_chain (struct hinic_api_cmd_chain*) ; 

void hinic_api_cmd_free(struct hinic_api_cmd_chain **chain)
{
	enum hinic_api_cmd_chain_type chain_type;

	chain_type = HINIC_API_CMD_WRITE_TO_MGMT_CPU;
	for ( ; chain_type < HINIC_API_CMD_MAX; chain_type++) {
		if (chain_type != HINIC_API_CMD_WRITE_TO_MGMT_CPU)
			continue;

		api_cmd_destroy_chain(chain[chain_type]);
	}
}