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
typedef  int u32 ;
struct iscsi_sess_err_stats {int digest_errors; int cxn_timeout_errors; int pdu_format_errors; int /*<<< orphan*/  lock; } ;
struct iscsi_tiqn {struct iscsi_sess_err_stats sess_err_stats; } ;
struct config_item {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct iscsi_tiqn* iscsi_instance_tiqn (struct config_item*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t iscsi_stat_instance_fail_sess_show(struct config_item *item,
		char *page)
{
	struct iscsi_tiqn *tiqn = iscsi_instance_tiqn(item);
	struct iscsi_sess_err_stats *sess_err = &tiqn->sess_err_stats;
	u32 sess_err_count;

	spin_lock_bh(&sess_err->lock);
	sess_err_count = (sess_err->digest_errors +
			  sess_err->cxn_timeout_errors +
			  sess_err->pdu_format_errors);
	spin_unlock_bh(&sess_err->lock);

	return snprintf(page, PAGE_SIZE, "%u\n", sess_err_count);
}