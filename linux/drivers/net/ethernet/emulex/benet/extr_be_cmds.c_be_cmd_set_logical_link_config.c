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
struct be_adapter {int dummy; } ;

/* Variables and functions */
 scalar_t__ BE2_chip (struct be_adapter*) ; 
 int EOPNOTSUPP ; 
 scalar_t__ MCC_STATUS_ILLEGAL_REQUEST ; 
 int __be_cmd_set_logical_link_config (struct be_adapter*,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ base_status (int) ; 

int be_cmd_set_logical_link_config(struct be_adapter *adapter,
				   int link_state, u8 domain)
{
	int status;

	if (BE2_chip(adapter))
		return -EOPNOTSUPP;

	status = __be_cmd_set_logical_link_config(adapter, link_state,
						  2, domain);

	/* Version 2 of the command will not be recognized by older FW.
	 * On such a failure issue version 1 of the command.
	 */
	if (base_status(status) == MCC_STATUS_ILLEGAL_REQUEST)
		status = __be_cmd_set_logical_link_config(adapter, link_state,
							  1, domain);
	return status;
}