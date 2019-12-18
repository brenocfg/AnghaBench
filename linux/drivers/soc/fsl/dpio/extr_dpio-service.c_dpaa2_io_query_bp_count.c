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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct qbman_swp {int dummy; } ;
struct qbman_bp_query_rslt {int dummy; } ;
struct dpaa2_io {int /*<<< orphan*/  lock_mgmt_cmd; struct qbman_swp* swp; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  qbman_bp_info_num_free_bufs (struct qbman_bp_query_rslt*) ; 
 int qbman_bp_query (struct qbman_swp*,int /*<<< orphan*/ ,struct qbman_bp_query_rslt*) ; 
 struct dpaa2_io* service_select (struct dpaa2_io*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int dpaa2_io_query_bp_count(struct dpaa2_io *d, u16 bpid, u32 *num)
{
	struct qbman_bp_query_rslt state;
	struct qbman_swp *swp;
	unsigned long irqflags;
	int ret;

	d = service_select(d);
	if (!d)
		return -ENODEV;

	swp = d->swp;
	spin_lock_irqsave(&d->lock_mgmt_cmd, irqflags);
	ret = qbman_bp_query(swp, bpid, &state);
	spin_unlock_irqrestore(&d->lock_mgmt_cmd, irqflags);
	if (ret)
		return ret;
	*num = qbman_bp_info_num_free_bufs(&state);
	return 0;
}