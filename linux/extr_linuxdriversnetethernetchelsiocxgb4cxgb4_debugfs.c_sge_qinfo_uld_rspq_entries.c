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
struct sge_uld_rxq_info {int /*<<< orphan*/  nrxq; int /*<<< orphan*/  nciq; } ;
struct TYPE_2__ {struct sge_uld_rxq_info** uld_rxq_info; } ;
struct adapter {TYPE_1__ sge; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sge_qinfo_uld_rspq_entries(const struct adapter *adap, int uld,
				      bool ciq)
{
	const struct sge_uld_rxq_info *urxq_info = adap->sge.uld_rxq_info[uld];

	if (!urxq_info)
		return 0;

	return ciq ? DIV_ROUND_UP(urxq_info->nciq, 4) :
		     DIV_ROUND_UP(urxq_info->nrxq, 4);
}