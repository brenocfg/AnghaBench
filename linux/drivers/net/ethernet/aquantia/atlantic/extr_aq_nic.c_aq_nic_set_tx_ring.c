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
struct aq_ring_s {int dummy; } ;
struct aq_nic_s {struct aq_ring_s** aq_ring_tx; } ;

/* Variables and functions */

void aq_nic_set_tx_ring(struct aq_nic_s *self, unsigned int idx,
			struct aq_ring_s *ring)
{
	self->aq_ring_tx[idx] = ring;
}