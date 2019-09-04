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
typedef  scalar_t__ u64 ;
struct aq_vec_s {int dummy; } ;
struct aq_stats_s {scalar_t__ dpc; scalar_t__ dma_oct_tc; scalar_t__ dma_oct_rc; scalar_t__ dma_pkt_tc; scalar_t__ dma_pkt_rc; scalar_t__ bbtc; scalar_t__ mbtc; scalar_t__ ubtc; scalar_t__ bbrc; scalar_t__ mbrc; scalar_t__ ubrc; scalar_t__ bptc; scalar_t__ mptc; scalar_t__ uptc; scalar_t__ erpt; scalar_t__ bprc; scalar_t__ mprc; scalar_t__ uprc; } ;
struct aq_nic_s {unsigned int aq_vecs; struct aq_vec_s** aq_vec; int /*<<< orphan*/  aq_hw; TYPE_1__* aq_hw_ops; } ;
struct TYPE_2__ {struct aq_stats_s* (* hw_get_hw_stats ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  aq_vec_get_sw_stats (struct aq_vec_s*,scalar_t__*,unsigned int*) ; 
 struct aq_stats_s* stub1 (int /*<<< orphan*/ ) ; 

void aq_nic_get_stats(struct aq_nic_s *self, u64 *data)
{
	unsigned int i = 0U;
	unsigned int count = 0U;
	struct aq_vec_s *aq_vec = NULL;
	struct aq_stats_s *stats = self->aq_hw_ops->hw_get_hw_stats(self->aq_hw);

	if (!stats)
		goto err_exit;

	data[i] = stats->uprc + stats->mprc + stats->bprc;
	data[++i] = stats->uprc;
	data[++i] = stats->mprc;
	data[++i] = stats->bprc;
	data[++i] = stats->erpt;
	data[++i] = stats->uptc + stats->mptc + stats->bptc;
	data[++i] = stats->uptc;
	data[++i] = stats->mptc;
	data[++i] = stats->bptc;
	data[++i] = stats->ubrc;
	data[++i] = stats->ubtc;
	data[++i] = stats->mbrc;
	data[++i] = stats->mbtc;
	data[++i] = stats->bbrc;
	data[++i] = stats->bbtc;
	data[++i] = stats->ubrc + stats->mbrc + stats->bbrc;
	data[++i] = stats->ubtc + stats->mbtc + stats->bbtc;
	data[++i] = stats->dma_pkt_rc;
	data[++i] = stats->dma_pkt_tc;
	data[++i] = stats->dma_oct_rc;
	data[++i] = stats->dma_oct_tc;
	data[++i] = stats->dpc;

	i++;

	data += i;

	for (i = 0U, aq_vec = self->aq_vec[0];
		aq_vec && self->aq_vecs > i; ++i, aq_vec = self->aq_vec[i]) {
		data += count;
		aq_vec_get_sw_stats(aq_vec, data, &count);
	}

err_exit:;
}