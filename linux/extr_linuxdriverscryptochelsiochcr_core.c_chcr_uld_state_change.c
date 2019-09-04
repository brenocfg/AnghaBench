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
struct uld_ctx {int /*<<< orphan*/  dev; } ;
typedef  enum cxgb4_state { ____Placeholder_cxgb4_state } cxgb4_state ;

/* Variables and functions */
#define  CXGB4_STATE_DETACH 131 
#define  CXGB4_STATE_DOWN 130 
#define  CXGB4_STATE_START_RECOVERY 129 
#define  CXGB4_STATE_UP 128 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int chcr_dev_add (struct uld_ctx*) ; 
 int /*<<< orphan*/  chcr_dev_remove (struct uld_ctx*) ; 
 int /*<<< orphan*/  dev_count ; 
 int /*<<< orphan*/  dev_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int start_crypto () ; 
 int /*<<< orphan*/  stop_crypto () ; 

__attribute__((used)) static int chcr_uld_state_change(void *handle, enum cxgb4_state state)
{
	struct uld_ctx *u_ctx = handle;
	int ret = 0;

	switch (state) {
	case CXGB4_STATE_UP:
		if (!u_ctx->dev) {
			ret = chcr_dev_add(u_ctx);
			if (ret != 0)
				return ret;
		}
		if (atomic_read(&dev_count) == 1)
			ret = start_crypto();
		break;

	case CXGB4_STATE_DETACH:
		if (u_ctx->dev) {
			mutex_lock(&dev_mutex);
			chcr_dev_remove(u_ctx);
			mutex_unlock(&dev_mutex);
		}
		if (!atomic_read(&dev_count))
			stop_crypto();
		break;

	case CXGB4_STATE_START_RECOVERY:
	case CXGB4_STATE_DOWN:
	default:
		break;
	}
	return ret;
}