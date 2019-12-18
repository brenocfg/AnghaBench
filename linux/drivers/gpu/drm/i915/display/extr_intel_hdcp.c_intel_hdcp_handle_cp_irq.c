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
struct intel_hdcp {int /*<<< orphan*/  check_work; int /*<<< orphan*/  cp_irq_queue; int /*<<< orphan*/  cp_irq_count; int /*<<< orphan*/  shim; } ;
struct intel_connector {struct intel_hdcp hdcp; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

void intel_hdcp_handle_cp_irq(struct intel_connector *connector)
{
	struct intel_hdcp *hdcp = &connector->hdcp;

	if (!hdcp->shim)
		return;

	atomic_inc(&connector->hdcp.cp_irq_count);
	wake_up_all(&connector->hdcp.cp_irq_queue);

	schedule_delayed_work(&hdcp->check_work, 0);
}