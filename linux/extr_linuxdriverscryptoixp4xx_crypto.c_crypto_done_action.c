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
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  RECV_QID ; 
 int /*<<< orphan*/  crypto_done_tasklet ; 
 int /*<<< orphan*/  one_packet (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qmgr_get_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void crypto_done_action(unsigned long arg)
{
	int i;

	for(i=0; i<4; i++) {
		dma_addr_t phys = qmgr_get_entry(RECV_QID);
		if (!phys)
			return;
		one_packet(phys);
	}
	tasklet_schedule(&crypto_done_tasklet);
}