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
struct sge {int /*<<< orphan*/  uld_rxq_info; int /*<<< orphan*/  uld_txq_info; } ;
struct adapter {int /*<<< orphan*/  uld; struct sge sge; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

void t4_uld_mem_free(struct adapter *adap)
{
	struct sge *s = &adap->sge;

	kfree(s->uld_txq_info);
	kfree(s->uld_rxq_info);
	kfree(adap->uld);
}