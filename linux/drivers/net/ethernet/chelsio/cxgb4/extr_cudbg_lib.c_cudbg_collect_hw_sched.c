#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct cudbg_init {struct adapter* adap; } ;
struct cudbg_hw_sched {int /*<<< orphan*/ * ipg; int /*<<< orphan*/ * kbps; int /*<<< orphan*/  pace_tab; int /*<<< orphan*/  mode; int /*<<< orphan*/  map; } ;
struct cudbg_error {int dummy; } ;
struct cudbg_buffer {scalar_t__ data; int /*<<< orphan*/  member_0; } ;
struct TYPE_3__ {int /*<<< orphan*/  cclk; } ;
struct TYPE_4__ {TYPE_1__ vpd; } ;
struct adapter {TYPE_2__ params; } ;

/* Variables and functions */
 int CUDBG_STATUS_CCLK_NOT_DEFINED ; 
 int NTX_SCHED ; 
 int /*<<< orphan*/  TIMERMODE_G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TP_MOD_CONFIG_A ; 
 int /*<<< orphan*/  TP_TX_MOD_QUEUE_REQ_MAP_A ; 
 int cudbg_get_buff (struct cudbg_init*,struct cudbg_buffer*,int,struct cudbg_buffer*) ; 
 int cudbg_write_and_release_buff (struct cudbg_init*,struct cudbg_buffer*,struct cudbg_buffer*) ; 
 int /*<<< orphan*/  t4_get_tx_sched (struct adapter*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  t4_read_pace_tbl (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 

int cudbg_collect_hw_sched(struct cudbg_init *pdbg_init,
			   struct cudbg_buffer *dbg_buff,
			   struct cudbg_error *cudbg_err)
{
	struct adapter *padap = pdbg_init->adap;
	struct cudbg_buffer temp_buff = { 0 };
	struct cudbg_hw_sched *hw_sched_buff;
	int i, rc = 0;

	if (!padap->params.vpd.cclk)
		return CUDBG_STATUS_CCLK_NOT_DEFINED;

	rc = cudbg_get_buff(pdbg_init, dbg_buff, sizeof(struct cudbg_hw_sched),
			    &temp_buff);

	if (rc)
		return rc;

	hw_sched_buff = (struct cudbg_hw_sched *)temp_buff.data;
	hw_sched_buff->map = t4_read_reg(padap, TP_TX_MOD_QUEUE_REQ_MAP_A);
	hw_sched_buff->mode = TIMERMODE_G(t4_read_reg(padap, TP_MOD_CONFIG_A));
	t4_read_pace_tbl(padap, hw_sched_buff->pace_tab);
	for (i = 0; i < NTX_SCHED; ++i)
		t4_get_tx_sched(padap, i, &hw_sched_buff->kbps[i],
				&hw_sched_buff->ipg[i], true);
	return cudbg_write_and_release_buff(pdbg_init, &temp_buff, dbg_buff);
}