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
struct sge_uld_rxq_info {int /*<<< orphan*/  nciq; scalar_t__ nrxq; scalar_t__ rspq_id; } ;
struct cxgb4_lld_info {int /*<<< orphan*/  nciq; scalar_t__ ciq_ids; scalar_t__ nrxq; scalar_t__ rxq_ids; } ;
struct TYPE_2__ {struct sge_uld_rxq_info** uld_rxq_info; } ;
struct adapter {TYPE_1__ sge; } ;

/* Variables and functions */

__attribute__((used)) static void uld_queue_init(struct adapter *adap, unsigned int uld_type,
			   struct cxgb4_lld_info *lli)
{
	struct sge_uld_rxq_info *rxq_info = adap->sge.uld_rxq_info[uld_type];

	lli->rxq_ids = rxq_info->rspq_id;
	lli->nrxq = rxq_info->nrxq;
	lli->ciq_ids = rxq_info->rspq_id + rxq_info->nrxq;
	lli->nciq = rxq_info->nciq;
}