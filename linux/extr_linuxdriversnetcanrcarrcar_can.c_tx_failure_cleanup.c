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
struct net_device {int dummy; } ;

/* Variables and functions */
 int RCAR_CAN_FIFO_DEPTH ; 
 int /*<<< orphan*/  can_free_echo_skb (struct net_device*,int) ; 

__attribute__((used)) static void tx_failure_cleanup(struct net_device *ndev)
{
	int i;

	for (i = 0; i < RCAR_CAN_FIFO_DEPTH; i++)
		can_free_echo_skb(ndev, i);
}