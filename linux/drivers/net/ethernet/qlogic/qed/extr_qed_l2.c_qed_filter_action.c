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
typedef  enum qed_filter_opcode { ____Placeholder_qed_filter_opcode } qed_filter_opcode ;
typedef  enum eth_filter_action { ____Placeholder_eth_filter_action } eth_filter_action ;

/* Variables and functions */
 int ETH_FILTER_ACTION_ADD ; 
 int ETH_FILTER_ACTION_REMOVE ; 
 int ETH_FILTER_ACTION_REMOVE_ALL ; 
 int MAX_ETH_FILTER_ACTION ; 
#define  QED_FILTER_ADD 130 
#define  QED_FILTER_FLUSH 129 
#define  QED_FILTER_REMOVE 128 

__attribute__((used)) static enum eth_filter_action qed_filter_action(enum qed_filter_opcode opcode)
{
	enum eth_filter_action action = MAX_ETH_FILTER_ACTION;

	switch (opcode) {
	case QED_FILTER_ADD:
		action = ETH_FILTER_ACTION_ADD;
		break;
	case QED_FILTER_REMOVE:
		action = ETH_FILTER_ACTION_REMOVE;
		break;
	case QED_FILTER_FLUSH:
		action = ETH_FILTER_ACTION_REMOVE_ALL;
		break;
	default:
		action = MAX_ETH_FILTER_ACTION;
	}

	return action;
}