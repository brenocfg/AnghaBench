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
struct sge_uld_txq_info {struct sge_uld_txq_info* uldtxq; int /*<<< orphan*/  users; } ;
struct TYPE_2__ {struct sge_uld_txq_info** uld_txq_info; } ;
struct adapter {TYPE_1__ sge; } ;

/* Variables and functions */
 int TX_ULD (unsigned int) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_sge_txq_uld (struct adapter*,struct sge_uld_txq_info*) ; 
 int /*<<< orphan*/  kfree (struct sge_uld_txq_info*) ; 

__attribute__((used)) static void
release_sge_txq_uld(struct adapter *adap, unsigned int uld_type)
{
	struct sge_uld_txq_info *txq_info = NULL;
	int tx_uld_type = TX_ULD(uld_type);

	txq_info = adap->sge.uld_txq_info[tx_uld_type];

	if (txq_info && atomic_dec_and_test(&txq_info->users)) {
		free_sge_txq_uld(adap, txq_info);
		kfree(txq_info->uldtxq);
		kfree(txq_info);
		adap->sge.uld_txq_info[tx_uld_type] = NULL;
	}
}