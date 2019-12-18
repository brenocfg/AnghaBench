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
struct xenvif {int /*<<< orphan*/  disabled; int /*<<< orphan*/  status; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  VIF_STATUS_CONNECTED ; 
 scalar_t__ netif_running (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int xenvif_schedulable(struct xenvif *vif)
{
	return netif_running(vif->dev) &&
		test_bit(VIF_STATUS_CONNECTED, &vif->status) &&
		!vif->disabled;
}