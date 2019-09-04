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
struct cudbg_pm_stats {int /*<<< orphan*/  rx_cyc; int /*<<< orphan*/  rx_cnt; int /*<<< orphan*/  tx_cyc; int /*<<< orphan*/  tx_cnt; } ;
struct cudbg_init {struct adapter* adap; } ;
struct cudbg_error {int dummy; } ;
struct cudbg_buffer {scalar_t__ data; int /*<<< orphan*/  member_0; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int cudbg_get_buff (struct cudbg_init*,struct cudbg_buffer*,int,struct cudbg_buffer*) ; 
 int cudbg_write_and_release_buff (struct cudbg_init*,struct cudbg_buffer*,struct cudbg_buffer*) ; 
 int /*<<< orphan*/  t4_pmrx_get_stats (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_pmtx_get_stats (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int cudbg_collect_pm_stats(struct cudbg_init *pdbg_init,
			   struct cudbg_buffer *dbg_buff,
			   struct cudbg_error *cudbg_err)
{
	struct adapter *padap = pdbg_init->adap;
	struct cudbg_buffer temp_buff = { 0 };
	struct cudbg_pm_stats *pm_stats_buff;
	int rc;

	rc = cudbg_get_buff(pdbg_init, dbg_buff, sizeof(struct cudbg_pm_stats),
			    &temp_buff);
	if (rc)
		return rc;

	pm_stats_buff = (struct cudbg_pm_stats *)temp_buff.data;
	t4_pmtx_get_stats(padap, pm_stats_buff->tx_cnt, pm_stats_buff->tx_cyc);
	t4_pmrx_get_stats(padap, pm_stats_buff->rx_cnt, pm_stats_buff->rx_cyc);
	return cudbg_write_and_release_buff(pdbg_init, &temp_buff, dbg_buff);
}