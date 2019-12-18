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
struct srpt_rdma_ch {int /*<<< orphan*/  kref; int /*<<< orphan*/  release_work; TYPE_1__* qp; int /*<<< orphan*/  sess_name; } ;
struct TYPE_2__ {int /*<<< orphan*/  qp_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  CH_DISCONNECTED ; 
 int /*<<< orphan*/  CH_DRAINING ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int srpt_ch_qp_err (struct srpt_rdma_ch*) ; 
 int /*<<< orphan*/  srpt_free_ch ; 
 scalar_t__ srpt_set_ch_state (struct srpt_rdma_ch*,int /*<<< orphan*/ ) ; 
 int srpt_zerolength_write (struct srpt_rdma_ch*) ; 

__attribute__((used)) static bool srpt_close_ch(struct srpt_rdma_ch *ch)
{
	int ret;

	if (!srpt_set_ch_state(ch, CH_DRAINING)) {
		pr_debug("%s: already closed\n", ch->sess_name);
		return false;
	}

	kref_get(&ch->kref);

	ret = srpt_ch_qp_err(ch);
	if (ret < 0)
		pr_err("%s-%d: changing queue pair into error state failed: %d\n",
		       ch->sess_name, ch->qp->qp_num, ret);

	ret = srpt_zerolength_write(ch);
	if (ret < 0) {
		pr_err("%s-%d: queuing zero-length write failed: %d\n",
		       ch->sess_name, ch->qp->qp_num, ret);
		if (srpt_set_ch_state(ch, CH_DISCONNECTED))
			schedule_work(&ch->release_work);
		else
			WARN_ON_ONCE(true);
	}

	kref_put(&ch->kref, srpt_free_ch);

	return true;
}