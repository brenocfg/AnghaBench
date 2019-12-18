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
struct htc_target {int /*<<< orphan*/  rx_lock; TYPE_1__* endpoint; } ;
typedef  enum htc_endpoint_id { ____Placeholder_htc_endpoint_id } htc_endpoint_id ;
struct TYPE_2__ {int /*<<< orphan*/  rx_bufq; } ;

/* Variables and functions */
 int get_queue_depth (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ath6kl_htc_pipe_get_rxbuf_num(struct htc_target *target,
					 enum htc_endpoint_id endpoint)
{
	int num;

	spin_lock_bh(&target->rx_lock);
	num = get_queue_depth(&(target->endpoint[endpoint].rx_bufq));
	spin_unlock_bh(&target->rx_lock);

	return num;
}