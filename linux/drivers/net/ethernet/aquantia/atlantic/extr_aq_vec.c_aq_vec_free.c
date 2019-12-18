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
struct aq_vec_s {unsigned int tx_rings; int /*<<< orphan*/  napi; struct aq_ring_s** ring; } ;
struct aq_ring_s {int dummy; } ;

/* Variables and functions */
 size_t AQ_VEC_RX_ID ; 
 size_t AQ_VEC_TX_ID ; 
 int /*<<< orphan*/  aq_ring_free (struct aq_ring_s*) ; 
 int /*<<< orphan*/  kfree (struct aq_vec_s*) ; 
 int /*<<< orphan*/  netif_napi_del (int /*<<< orphan*/ *) ; 

void aq_vec_free(struct aq_vec_s *self)
{
	struct aq_ring_s *ring = NULL;
	unsigned int i = 0U;

	if (!self)
		goto err_exit;

	for (i = 0U, ring = self->ring[0];
		self->tx_rings > i; ++i, ring = self->ring[i]) {
		aq_ring_free(&ring[AQ_VEC_TX_ID]);
		aq_ring_free(&ring[AQ_VEC_RX_ID]);
	}

	netif_napi_del(&self->napi);

	kfree(self);

err_exit:;
}