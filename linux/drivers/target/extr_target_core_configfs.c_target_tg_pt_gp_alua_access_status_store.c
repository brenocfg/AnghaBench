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
struct t10_alua_tg_pt_gp {int tg_pt_gp_valid_id; int tg_pt_gp_alua_access_status; } ;
struct config_item {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int ALUA_STATUS_ALTERED_BY_EXPLICIT_STPG ; 
 int ALUA_STATUS_ALTERED_BY_IMPLICIT_ALUA ; 
 int ALUA_STATUS_NONE ; 
 int EINVAL ; 
 int kstrtoul (char const*,int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 struct t10_alua_tg_pt_gp* to_tg_pt_gp (struct config_item*) ; 

__attribute__((used)) static ssize_t target_tg_pt_gp_alua_access_status_store(
		struct config_item *item, const char *page, size_t count)
{
	struct t10_alua_tg_pt_gp *tg_pt_gp = to_tg_pt_gp(item);
	unsigned long tmp;
	int new_status, ret;

	if (!tg_pt_gp->tg_pt_gp_valid_id) {
		pr_err("Unable to do set ALUA access status on non"
			" valid tg_pt_gp ID: %hu\n",
			tg_pt_gp->tg_pt_gp_valid_id);
		return -EINVAL;
	}

	ret = kstrtoul(page, 0, &tmp);
	if (ret < 0) {
		pr_err("Unable to extract new ALUA access status"
				" from %s\n", page);
		return ret;
	}
	new_status = (int)tmp;

	if ((new_status != ALUA_STATUS_NONE) &&
	    (new_status != ALUA_STATUS_ALTERED_BY_EXPLICIT_STPG) &&
	    (new_status != ALUA_STATUS_ALTERED_BY_IMPLICIT_ALUA)) {
		pr_err("Illegal ALUA access status: 0x%02x\n",
				new_status);
		return -EINVAL;
	}

	tg_pt_gp->tg_pt_gp_alua_access_status = new_status;
	return count;
}