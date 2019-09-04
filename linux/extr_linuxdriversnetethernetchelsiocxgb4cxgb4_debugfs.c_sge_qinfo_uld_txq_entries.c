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
struct sge_uld_txq_info {int /*<<< orphan*/  ntxq; } ;
struct TYPE_2__ {struct sge_uld_txq_info** uld_txq_info; } ;
struct adapter {TYPE_1__ sge; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sge_qinfo_uld_txq_entries(const struct adapter *adap, int uld)
{
	const struct sge_uld_txq_info *utxq_info = adap->sge.uld_txq_info[uld];

	if (!utxq_info)
		return 0;

	return DIV_ROUND_UP(utxq_info->ntxq, 4);
}