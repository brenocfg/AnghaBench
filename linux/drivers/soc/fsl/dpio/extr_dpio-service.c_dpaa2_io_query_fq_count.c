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
struct qbman_swp {int dummy; } ;
struct qbman_fq_query_np_rslt {int dummy; } ;
struct dpaa2_io {int /*<<< orphan*/  lock_mgmt_cmd; struct qbman_swp* swp; } ;

/* Variables and functions */
 int ENODEV ; 
 int qbman_fq_query_state (struct qbman_swp*,int /*<<< orphan*/ ,struct qbman_fq_query_np_rslt*) ; 
 int /*<<< orphan*/  qbman_fq_state_byte_count (struct qbman_fq_query_np_rslt*) ; 
 int /*<<< orphan*/  qbman_fq_state_frame_count (struct qbman_fq_query_np_rslt*) ; 
 struct dpaa2_io* service_select (struct dpaa2_io*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int dpaa2_io_query_fq_count(struct dpaa2_io *d, u32 fqid,
			    u32 *fcnt, u32 *bcnt)
{
	struct qbman_fq_query_np_rslt state;
	struct qbman_swp *swp;
	unsigned long irqflags;
	int ret;

	d = service_select(d);
	if (!d)
		return -ENODEV;

	swp = d->swp;
	spin_lock_irqsave(&d->lock_mgmt_cmd, irqflags);
	ret = qbman_fq_query_state(swp, fqid, &state);
	spin_unlock_irqrestore(&d->lock_mgmt_cmd, irqflags);
	if (ret)
		return ret;
	*fcnt = qbman_fq_state_frame_count(&state);
	*bcnt = qbman_fq_state_byte_count(&state);

	return 0;
}