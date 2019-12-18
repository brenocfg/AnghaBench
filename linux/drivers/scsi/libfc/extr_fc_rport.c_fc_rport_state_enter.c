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
struct fc_rport_priv {int rp_state; scalar_t__ retries; int /*<<< orphan*/  rp_mutex; } ;
typedef  enum fc_rport_state { ____Placeholder_fc_rport_state } fc_rport_state ;

/* Variables and functions */
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fc_rport_state_enter(struct fc_rport_priv *rdata,
				 enum fc_rport_state new)
{
	lockdep_assert_held(&rdata->rp_mutex);

	if (rdata->rp_state != new)
		rdata->retries = 0;
	rdata->rp_state = new;
}