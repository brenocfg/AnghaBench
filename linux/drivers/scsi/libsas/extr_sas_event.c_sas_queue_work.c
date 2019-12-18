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
struct sas_work {int /*<<< orphan*/  work; int /*<<< orphan*/  drain_node; } ;
struct sas_ha_struct {int /*<<< orphan*/  event_q; int /*<<< orphan*/  defer_q; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAS_HA_DRAINING ; 
 int /*<<< orphan*/  SAS_HA_REGISTERED ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int sas_queue_work(struct sas_ha_struct *ha, struct sas_work *sw)
{
	/* it's added to the defer_q when draining so return succeed */
	int rc = 1;

	if (!test_bit(SAS_HA_REGISTERED, &ha->state))
		return 0;

	if (test_bit(SAS_HA_DRAINING, &ha->state)) {
		/* add it to the defer list, if not already pending */
		if (list_empty(&sw->drain_node))
			list_add_tail(&sw->drain_node, &ha->defer_q);
	} else
		rc = queue_work(ha->event_q, &sw->work);

	return rc;
}