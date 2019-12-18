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
struct sge_txq {int dummy; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  reclaim_completed_tx (struct adapter*,struct sge_txq*,int,int) ; 

void cxgb4_reclaim_completed_tx(struct adapter *adap, struct sge_txq *q,
				bool unmap)
{
	(void)reclaim_completed_tx(adap, q, -1, unmap);
}