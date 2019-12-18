#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct lancer_pport_stats {int dummy; } ;
struct lancer_cmd_resp_pport_stats {struct lancer_pport_stats pport_stats; } ;
struct TYPE_2__ {struct lancer_cmd_resp_pport_stats* va; } ;
struct be_adapter {TYPE_1__ stats_cmd; } ;

/* Variables and functions */

__attribute__((used)) static inline struct lancer_pport_stats*
	pport_stats_from_cmd(struct be_adapter *adapter)
{
	struct lancer_cmd_resp_pport_stats *cmd = adapter->stats_cmd.va;
	return &cmd->pport_stats;
}