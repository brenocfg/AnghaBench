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
struct cudbg_init {struct adapter* adap; } ;
struct cudbg_error {int sys_err; } ;
struct cudbg_cim_qcfg {int /*<<< orphan*/  thres; int /*<<< orphan*/  size; int /*<<< orphan*/  base; int /*<<< orphan*/  obq_wr; int /*<<< orphan*/  stat; int /*<<< orphan*/  chip; } ;
struct cudbg_buffer {scalar_t__ data; int /*<<< orphan*/  member_0; } ;
struct TYPE_2__ {int /*<<< orphan*/  chip; } ;
struct adapter {TYPE_1__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UP_IBQ_0_RDADDR_A ; 
 int /*<<< orphan*/  UP_OBQ_0_REALADDR_A ; 
 int cudbg_get_buff (struct cudbg_init*,struct cudbg_buffer*,int,struct cudbg_buffer*) ; 
 int /*<<< orphan*/  cudbg_put_buff (struct cudbg_init*,struct cudbg_buffer*) ; 
 int cudbg_write_and_release_buff (struct cudbg_init*,struct cudbg_buffer*,struct cudbg_buffer*) ; 
 int t4_cim_read (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_read_cimq_cfg (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int cudbg_collect_cim_qcfg(struct cudbg_init *pdbg_init,
			   struct cudbg_buffer *dbg_buff,
			   struct cudbg_error *cudbg_err)
{
	struct adapter *padap = pdbg_init->adap;
	struct cudbg_buffer temp_buff = { 0 };
	struct cudbg_cim_qcfg *cim_qcfg_data;
	int rc;

	rc = cudbg_get_buff(pdbg_init, dbg_buff, sizeof(struct cudbg_cim_qcfg),
			    &temp_buff);
	if (rc)
		return rc;

	cim_qcfg_data = (struct cudbg_cim_qcfg *)temp_buff.data;
	cim_qcfg_data->chip = padap->params.chip;
	rc = t4_cim_read(padap, UP_IBQ_0_RDADDR_A,
			 ARRAY_SIZE(cim_qcfg_data->stat), cim_qcfg_data->stat);
	if (rc) {
		cudbg_err->sys_err = rc;
		cudbg_put_buff(pdbg_init, &temp_buff);
		return rc;
	}

	rc = t4_cim_read(padap, UP_OBQ_0_REALADDR_A,
			 ARRAY_SIZE(cim_qcfg_data->obq_wr),
			 cim_qcfg_data->obq_wr);
	if (rc) {
		cudbg_err->sys_err = rc;
		cudbg_put_buff(pdbg_init, &temp_buff);
		return rc;
	}

	t4_read_cimq_cfg(padap, cim_qcfg_data->base, cim_qcfg_data->size,
			 cim_qcfg_data->thres);
	return cudbg_write_and_release_buff(pdbg_init, &temp_buff, dbg_buff);
}