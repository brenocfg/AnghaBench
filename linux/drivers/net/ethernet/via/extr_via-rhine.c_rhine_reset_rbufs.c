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
struct rhine_private {TYPE_1__* rx_ring; scalar_t__ cur_rx; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  DescOwn ; 
 int RX_RING_SIZE ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rhine_reset_rbufs(struct rhine_private *rp)
{
	int i;

	rp->cur_rx = 0;

	for (i = 0; i < RX_RING_SIZE; i++)
		rp->rx_ring[i].rx_status = cpu_to_le32(DescOwn);
}