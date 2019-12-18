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
struct sge_uld_rxq_info {struct sge_uld_rxq_info* uldrxq; struct sge_uld_rxq_info* rspq_id; } ;
struct TYPE_2__ {struct sge_uld_rxq_info** uld_rxq_info; } ;
struct adapter {TYPE_1__ sge; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct sge_uld_rxq_info*) ; 

__attribute__((used)) static void free_queues_uld(struct adapter *adap, unsigned int uld_type)
{
	struct sge_uld_rxq_info *rxq_info = adap->sge.uld_rxq_info[uld_type];

	adap->sge.uld_rxq_info[uld_type] = NULL;
	kfree(rxq_info->rspq_id);
	kfree(rxq_info->uldrxq);
	kfree(rxq_info);
}