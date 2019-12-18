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
struct target_core_fabric_ops {int /*<<< orphan*/  fabric_drop_tpg; int /*<<< orphan*/  fabric_make_tpg; int /*<<< orphan*/  fabric_drop_wwn; int /*<<< orphan*/  fabric_make_wwn; int /*<<< orphan*/  check_stop_free; int /*<<< orphan*/  aborted_task; int /*<<< orphan*/  queue_tm_rsp; int /*<<< orphan*/  queue_status; int /*<<< orphan*/  queue_data_in; int /*<<< orphan*/  get_cmd_state; int /*<<< orphan*/  set_default_node_attributes; int /*<<< orphan*/  write_pending; int /*<<< orphan*/  sess_get_index; int /*<<< orphan*/  release_cmd; int /*<<< orphan*/  tpg_get_inst_index; int /*<<< orphan*/  tpg_check_prod_mode_write_protect; int /*<<< orphan*/  tpg_check_demo_mode_write_protect; int /*<<< orphan*/  tpg_check_demo_mode_cache; int /*<<< orphan*/  tpg_check_demo_mode; int /*<<< orphan*/  tpg_get_tag; int /*<<< orphan*/  tpg_get_wwn; scalar_t__ fabric_name; scalar_t__ fabric_alias; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ TARGET_FABRIC_NAME_SIZE ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 scalar_t__ strlen (scalar_t__) ; 

__attribute__((used)) static int target_fabric_tf_ops_check(const struct target_core_fabric_ops *tfo)
{
	if (tfo->fabric_alias) {
		if (strlen(tfo->fabric_alias) >= TARGET_FABRIC_NAME_SIZE) {
			pr_err("Passed alias: %s exceeds "
				"TARGET_FABRIC_NAME_SIZE\n", tfo->fabric_alias);
			return -EINVAL;
		}
	}
	if (!tfo->fabric_name) {
		pr_err("Missing tfo->fabric_name\n");
		return -EINVAL;
	}
	if (strlen(tfo->fabric_name) >= TARGET_FABRIC_NAME_SIZE) {
		pr_err("Passed name: %s exceeds "
			"TARGET_FABRIC_NAME_SIZE\n", tfo->fabric_name);
		return -EINVAL;
	}
	if (!tfo->tpg_get_wwn) {
		pr_err("Missing tfo->tpg_get_wwn()\n");
		return -EINVAL;
	}
	if (!tfo->tpg_get_tag) {
		pr_err("Missing tfo->tpg_get_tag()\n");
		return -EINVAL;
	}
	if (!tfo->tpg_check_demo_mode) {
		pr_err("Missing tfo->tpg_check_demo_mode()\n");
		return -EINVAL;
	}
	if (!tfo->tpg_check_demo_mode_cache) {
		pr_err("Missing tfo->tpg_check_demo_mode_cache()\n");
		return -EINVAL;
	}
	if (!tfo->tpg_check_demo_mode_write_protect) {
		pr_err("Missing tfo->tpg_check_demo_mode_write_protect()\n");
		return -EINVAL;
	}
	if (!tfo->tpg_check_prod_mode_write_protect) {
		pr_err("Missing tfo->tpg_check_prod_mode_write_protect()\n");
		return -EINVAL;
	}
	if (!tfo->tpg_get_inst_index) {
		pr_err("Missing tfo->tpg_get_inst_index()\n");
		return -EINVAL;
	}
	if (!tfo->release_cmd) {
		pr_err("Missing tfo->release_cmd()\n");
		return -EINVAL;
	}
	if (!tfo->sess_get_index) {
		pr_err("Missing tfo->sess_get_index()\n");
		return -EINVAL;
	}
	if (!tfo->write_pending) {
		pr_err("Missing tfo->write_pending()\n");
		return -EINVAL;
	}
	if (!tfo->set_default_node_attributes) {
		pr_err("Missing tfo->set_default_node_attributes()\n");
		return -EINVAL;
	}
	if (!tfo->get_cmd_state) {
		pr_err("Missing tfo->get_cmd_state()\n");
		return -EINVAL;
	}
	if (!tfo->queue_data_in) {
		pr_err("Missing tfo->queue_data_in()\n");
		return -EINVAL;
	}
	if (!tfo->queue_status) {
		pr_err("Missing tfo->queue_status()\n");
		return -EINVAL;
	}
	if (!tfo->queue_tm_rsp) {
		pr_err("Missing tfo->queue_tm_rsp()\n");
		return -EINVAL;
	}
	if (!tfo->aborted_task) {
		pr_err("Missing tfo->aborted_task()\n");
		return -EINVAL;
	}
	if (!tfo->check_stop_free) {
		pr_err("Missing tfo->check_stop_free()\n");
		return -EINVAL;
	}
	/*
	 * We at least require tfo->fabric_make_wwn(), tfo->fabric_drop_wwn()
	 * tfo->fabric_make_tpg() and tfo->fabric_drop_tpg() in
	 * target_core_fabric_configfs.c WWN+TPG group context code.
	 */
	if (!tfo->fabric_make_wwn) {
		pr_err("Missing tfo->fabric_make_wwn()\n");
		return -EINVAL;
	}
	if (!tfo->fabric_drop_wwn) {
		pr_err("Missing tfo->fabric_drop_wwn()\n");
		return -EINVAL;
	}
	if (!tfo->fabric_make_tpg) {
		pr_err("Missing tfo->fabric_make_tpg()\n");
		return -EINVAL;
	}
	if (!tfo->fabric_drop_tpg) {
		pr_err("Missing tfo->fabric_drop_tpg()\n");
		return -EINVAL;
	}

	return 0;
}