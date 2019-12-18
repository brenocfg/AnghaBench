#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  rx_drops; int /*<<< orphan*/  rx_pkts; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  tx_pkts; int /*<<< orphan*/  tx_bytes; } ;
union efa_com_get_stats_result {TYPE_2__ basic_stats; } ;
struct efa_com_get_stats_params {int /*<<< orphan*/  scope_modifier; int /*<<< orphan*/  scope; int /*<<< orphan*/  type; } ;
struct efa_com_admin_queue {int dummy; } ;
struct efa_com_dev {int /*<<< orphan*/  efa_dev; struct efa_com_admin_queue aq; } ;
struct TYPE_4__ {int /*<<< orphan*/  opcode; } ;
struct efa_admin_aq_get_stats_cmd {int /*<<< orphan*/  scope_modifier; int /*<<< orphan*/  scope; int /*<<< orphan*/  type; TYPE_1__ aq_common_descriptor; } ;
struct efa_admin_aq_entry {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  rx_drops; int /*<<< orphan*/  rx_pkts; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  tx_pkts; int /*<<< orphan*/  tx_bytes; } ;
struct efa_admin_acq_get_stats_resp {TYPE_3__ basic_stats; } ;
struct efa_admin_acq_entry {int dummy; } ;
typedef  int /*<<< orphan*/  resp ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  EFA_ADMIN_GET_STATS ; 
 int efa_com_cmd_exec (struct efa_com_admin_queue*,struct efa_admin_aq_entry*,int,struct efa_admin_acq_entry*,int) ; 
 int /*<<< orphan*/  ibdev_err_ratelimited (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int efa_com_get_stats(struct efa_com_dev *edev,
		      struct efa_com_get_stats_params *params,
		      union efa_com_get_stats_result *result)
{
	struct efa_com_admin_queue *aq = &edev->aq;
	struct efa_admin_aq_get_stats_cmd cmd = {};
	struct efa_admin_acq_get_stats_resp resp;
	int err;

	cmd.aq_common_descriptor.opcode = EFA_ADMIN_GET_STATS;
	cmd.type = params->type;
	cmd.scope = params->scope;
	cmd.scope_modifier = params->scope_modifier;

	err = efa_com_cmd_exec(aq,
			       (struct efa_admin_aq_entry *)&cmd,
			       sizeof(cmd),
			       (struct efa_admin_acq_entry *)&resp,
			       sizeof(resp));
	if (err) {
		ibdev_err_ratelimited(
			edev->efa_dev,
			"Failed to get stats type-%u scope-%u.%u [%d]\n",
			cmd.type, cmd.scope, cmd.scope_modifier, err);
		return err;
	}

	result->basic_stats.tx_bytes = resp.basic_stats.tx_bytes;
	result->basic_stats.tx_pkts = resp.basic_stats.tx_pkts;
	result->basic_stats.rx_bytes = resp.basic_stats.rx_bytes;
	result->basic_stats.rx_pkts = resp.basic_stats.rx_pkts;
	result->basic_stats.rx_drops = resp.basic_stats.rx_drops;

	return 0;
}