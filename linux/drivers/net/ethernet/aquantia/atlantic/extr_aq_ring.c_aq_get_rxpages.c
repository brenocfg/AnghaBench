#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  pg_reuses; int /*<<< orphan*/  pg_losts; int /*<<< orphan*/  pg_flips; } ;
struct TYPE_6__ {TYPE_1__ rx; } ;
struct aq_ring_s {int /*<<< orphan*/  aq_nic; TYPE_2__ stats; } ;
struct TYPE_7__ {int pg_off; scalar_t__ page; } ;
struct aq_ring_buff_s {TYPE_3__ rxdata; } ;

/* Variables and functions */
 int AQ_CFG_RX_FRAME_MAX ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  aq_free_rxpage (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int aq_get_rxpage (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aq_nic_get_dev (int /*<<< orphan*/ ) ; 
 int page_ref_count (scalar_t__) ; 

__attribute__((used)) static int aq_get_rxpages(struct aq_ring_s *self, struct aq_ring_buff_s *rxbuf,
			  int order)
{
	int ret;

	if (rxbuf->rxdata.page) {
		/* One means ring is the only user and can reuse */
		if (page_ref_count(rxbuf->rxdata.page) > 1) {
			/* Try reuse buffer */
			rxbuf->rxdata.pg_off += AQ_CFG_RX_FRAME_MAX;
			if (rxbuf->rxdata.pg_off + AQ_CFG_RX_FRAME_MAX <=
				(PAGE_SIZE << order)) {
				self->stats.rx.pg_flips++;
			} else {
				/* Buffer exhausted. We have other users and
				 * should release this page and realloc
				 */
				aq_free_rxpage(&rxbuf->rxdata,
					       aq_nic_get_dev(self->aq_nic));
				self->stats.rx.pg_losts++;
			}
		} else {
			rxbuf->rxdata.pg_off = 0;
			self->stats.rx.pg_reuses++;
		}
	}

	if (!rxbuf->rxdata.page) {
		ret = aq_get_rxpage(&rxbuf->rxdata, order,
				    aq_nic_get_dev(self->aq_nic));
		return ret;
	}

	return 0;
}