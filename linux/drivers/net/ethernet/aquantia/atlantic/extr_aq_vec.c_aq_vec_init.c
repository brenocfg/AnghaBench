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
struct aq_vec_s {unsigned int tx_rings; struct aq_hw_s* aq_hw; struct aq_hw_ops const* aq_hw_ops; int /*<<< orphan*/  aq_ring_param; struct aq_ring_s** ring; } ;
struct aq_ring_s {int dummy; } ;
struct aq_hw_s {int dummy; } ;
struct aq_hw_ops {int (* hw_ring_tx_init ) (struct aq_hw_s*,struct aq_ring_s*,int /*<<< orphan*/ *) ;int (* hw_ring_rx_init ) (struct aq_hw_s*,struct aq_ring_s*,int /*<<< orphan*/ *) ;int (* hw_ring_rx_fill ) (struct aq_hw_s*,struct aq_ring_s*,unsigned int) ;} ;

/* Variables and functions */
 size_t AQ_VEC_RX_ID ; 
 size_t AQ_VEC_TX_ID ; 
 int aq_ring_init (struct aq_ring_s*) ; 
 int aq_ring_rx_fill (struct aq_ring_s*) ; 
 int stub1 (struct aq_hw_s*,struct aq_ring_s*,int /*<<< orphan*/ *) ; 
 int stub2 (struct aq_hw_s*,struct aq_ring_s*,int /*<<< orphan*/ *) ; 
 int stub3 (struct aq_hw_s*,struct aq_ring_s*,unsigned int) ; 

int aq_vec_init(struct aq_vec_s *self, const struct aq_hw_ops *aq_hw_ops,
		struct aq_hw_s *aq_hw)
{
	struct aq_ring_s *ring = NULL;
	unsigned int i = 0U;
	int err = 0;

	self->aq_hw_ops = aq_hw_ops;
	self->aq_hw = aq_hw;

	for (i = 0U, ring = self->ring[0];
		self->tx_rings > i; ++i, ring = self->ring[i]) {
		err = aq_ring_init(&ring[AQ_VEC_TX_ID]);
		if (err < 0)
			goto err_exit;

		err = self->aq_hw_ops->hw_ring_tx_init(self->aq_hw,
						       &ring[AQ_VEC_TX_ID],
						       &self->aq_ring_param);
		if (err < 0)
			goto err_exit;

		err = aq_ring_init(&ring[AQ_VEC_RX_ID]);
		if (err < 0)
			goto err_exit;

		err = self->aq_hw_ops->hw_ring_rx_init(self->aq_hw,
						       &ring[AQ_VEC_RX_ID],
						       &self->aq_ring_param);
		if (err < 0)
			goto err_exit;

		err = aq_ring_rx_fill(&ring[AQ_VEC_RX_ID]);
		if (err < 0)
			goto err_exit;

		err = self->aq_hw_ops->hw_ring_rx_fill(self->aq_hw,
						       &ring[AQ_VEC_RX_ID], 0U);
		if (err < 0)
			goto err_exit;
	}

err_exit:
	return err;
}