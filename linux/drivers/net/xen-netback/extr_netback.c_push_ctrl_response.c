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
struct xenvif {int /*<<< orphan*/  ctrl_irq; int /*<<< orphan*/  ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  RING_PUSH_RESPONSES_AND_CHECK_NOTIFY (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  notify_remote_via_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void push_ctrl_response(struct xenvif *vif)
{
	int notify;

	RING_PUSH_RESPONSES_AND_CHECK_NOTIFY(&vif->ctrl, notify);
	if (notify)
		notify_remote_via_irq(vif->ctrl_irq);
}