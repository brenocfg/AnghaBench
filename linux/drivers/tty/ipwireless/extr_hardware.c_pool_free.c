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
struct ipw_rx_packet {int /*<<< orphan*/  queue; } ;
struct ipw_hardware {int rx_pool_size; int /*<<< orphan*/  rx_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct ipw_rx_packet*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pool_free(struct ipw_hardware *hw, struct ipw_rx_packet *packet)
{
	if (hw->rx_pool_size > 6)
		kfree(packet);
	else {
		hw->rx_pool_size++;
		list_add(&packet->queue, &hw->rx_pool);
	}
}