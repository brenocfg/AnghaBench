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
struct cxlflash_cfg {int /*<<< orphan*/  ctx_tbl_list_mutex; int /*<<< orphan*/  ctx_err_recovery; struct ctx_info** ctx_tbl; } ;
struct ctx_info {int err_recovery_active; int /*<<< orphan*/  mutex; int /*<<< orphan*/ * ctrl_map; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int MAX_CONTEXT ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unmap_context (struct ctx_info*) ; 

int cxlflash_mark_contexts_error(struct cxlflash_cfg *cfg)
{
	int i, rc = 0;
	struct ctx_info *ctxi = NULL;

	mutex_lock(&cfg->ctx_tbl_list_mutex);

	for (i = 0; i < MAX_CONTEXT; i++) {
		ctxi = cfg->ctx_tbl[i];
		if (ctxi) {
			mutex_lock(&ctxi->mutex);
			cfg->ctx_tbl[i] = NULL;
			list_add(&ctxi->list, &cfg->ctx_err_recovery);
			ctxi->err_recovery_active = true;
			ctxi->ctrl_map = NULL;
			unmap_context(ctxi);
			mutex_unlock(&ctxi->mutex);
		}
	}

	mutex_unlock(&cfg->ctx_tbl_list_mutex);
	return rc;
}