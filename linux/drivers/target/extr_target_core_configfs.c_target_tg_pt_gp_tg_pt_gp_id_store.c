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
typedef  int /*<<< orphan*/  u16 ;
struct config_group {int /*<<< orphan*/  cg_item; } ;
struct t10_alua_tg_pt_gp {int /*<<< orphan*/  tg_pt_gp_id; struct config_group tg_pt_gp_group; } ;
struct config_item {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  config_item_name (int /*<<< orphan*/ *) ; 
 int core_alua_set_tg_pt_gp_id (struct t10_alua_tg_pt_gp*,int /*<<< orphan*/ ) ; 
 int kstrtoul (char const*,int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 struct t10_alua_tg_pt_gp* to_tg_pt_gp (struct config_item*) ; 

__attribute__((used)) static ssize_t target_tg_pt_gp_tg_pt_gp_id_store(struct config_item *item,
		const char *page, size_t count)
{
	struct t10_alua_tg_pt_gp *tg_pt_gp = to_tg_pt_gp(item);
	struct config_group *alua_tg_pt_gp_cg = &tg_pt_gp->tg_pt_gp_group;
	unsigned long tg_pt_gp_id;
	int ret;

	ret = kstrtoul(page, 0, &tg_pt_gp_id);
	if (ret < 0) {
		pr_err("ALUA tg_pt_gp_id: invalid value '%s' for tg_pt_gp_id\n",
		       page);
		return ret;
	}
	if (tg_pt_gp_id > 0x0000ffff) {
		pr_err("ALUA tg_pt_gp_id: %lu exceeds maximum: 0x0000ffff\n",
		       tg_pt_gp_id);
		return -EINVAL;
	}

	ret = core_alua_set_tg_pt_gp_id(tg_pt_gp, (u16)tg_pt_gp_id);
	if (ret < 0)
		return -EINVAL;

	pr_debug("Target_Core_ConfigFS: Set ALUA Target Port Group: "
		"core/alua/tg_pt_gps/%s to ID: %hu\n",
		config_item_name(&alua_tg_pt_gp_cg->cg_item),
		tg_pt_gp->tg_pt_gp_id);

	return count;
}