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
struct fc_rport_priv {scalar_t__ retries; int /*<<< orphan*/  kref; int /*<<< orphan*/  retry_work; TYPE_1__* local_port; int /*<<< orphan*/  rp_mutex; int /*<<< orphan*/  e_d_tov; } ;
struct TYPE_2__ {scalar_t__ max_rport_retry_count; } ;

/* Variables and functions */
 int FC_EX_CLOSED ; 
 int FC_EX_TIMEOUT ; 
 int /*<<< orphan*/  FC_RPORT_DBG (struct fc_rport_priv*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fc_rport_destroy ; 
 int /*<<< orphan*/  fc_rport_error (struct fc_rport_priv*,int) ; 
 int /*<<< orphan*/  fc_rport_state (struct fc_rport_priv*) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void fc_rport_error_retry(struct fc_rport_priv *rdata, int err)
{
	unsigned long delay = msecs_to_jiffies(rdata->e_d_tov);

	lockdep_assert_held(&rdata->rp_mutex);

	/* make sure this isn't an FC_EX_CLOSED error, never retry those */
	if (err == -FC_EX_CLOSED)
		goto out;

	if (rdata->retries < rdata->local_port->max_rport_retry_count) {
		FC_RPORT_DBG(rdata, "Error %d in state %s, retrying\n",
			     err, fc_rport_state(rdata));
		rdata->retries++;
		/* no additional delay on exchange timeouts */
		if (err == -FC_EX_TIMEOUT)
			delay = 0;
		kref_get(&rdata->kref);
		if (!schedule_delayed_work(&rdata->retry_work, delay))
			kref_put(&rdata->kref, fc_rport_destroy);
		return;
	}

out:
	fc_rport_error(rdata, err);
}