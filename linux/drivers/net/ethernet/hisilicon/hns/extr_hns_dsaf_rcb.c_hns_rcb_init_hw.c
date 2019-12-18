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
struct ring_pair_cb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RX_RING ; 
 int /*<<< orphan*/  TX_RING ; 
 int /*<<< orphan*/  hns_rcb_ring_init (struct ring_pair_cb*,int /*<<< orphan*/ ) ; 

void hns_rcb_init_hw(struct ring_pair_cb *ring)
{
	hns_rcb_ring_init(ring, RX_RING);
	hns_rcb_ring_init(ring, TX_RING);
}