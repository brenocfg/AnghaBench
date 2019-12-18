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
struct fc_lport {scalar_t__ retry_count; scalar_t__ max_retry_count; int e_d_tov; int /*<<< orphan*/  retry_work; } ;
struct fc_frame {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FC_EX_CLOSED ; 
 int /*<<< orphan*/  FC_LPORT_DBG (struct fc_lport*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ IS_ERR (struct fc_frame*) ; 
 int /*<<< orphan*/  PTR_ERR (struct fc_frame*) ; 
 int /*<<< orphan*/  fc_lport_enter_reset (struct fc_lport*) ; 
 int /*<<< orphan*/  fc_lport_state (struct fc_lport*) ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void fc_lport_error(struct fc_lport *lport, struct fc_frame *fp)
{
	unsigned long delay = 0;
	FC_LPORT_DBG(lport, "Error %ld in state %s, retries %d\n",
		     IS_ERR(fp) ? -PTR_ERR(fp) : 0, fc_lport_state(lport),
		     lport->retry_count);

	if (PTR_ERR(fp) == -FC_EX_CLOSED)
		return;

	/*
	 * Memory allocation failure, or the exchange timed out
	 * or we received LS_RJT.
	 * Retry after delay
	 */
	if (lport->retry_count < lport->max_retry_count) {
		lport->retry_count++;
		if (!fp)
			delay = msecs_to_jiffies(500);
		else
			delay =	msecs_to_jiffies(lport->e_d_tov);

		schedule_delayed_work(&lport->retry_work, delay);
	} else
		fc_lport_enter_reset(lport);
}