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
typedef  int /*<<< orphan*/  u32 ;
struct sge_qbase_reg_field {int vfcount; void** reg_data; void* reg_addr; } ;
struct ireg_field {void* ireg_local_offset; void* ireg_offset_range; void* ireg_data; void* ireg_addr; } ;
struct ireg_buf {int /*<<< orphan*/ * outbuf; struct ireg_field tp_pio; } ;
struct cudbg_init {struct adapter* adap; } ;
struct cudbg_error {int dummy; } ;
struct cudbg_buffer {scalar_t__ data; int /*<<< orphan*/  member_0; } ;
struct TYPE_3__ {int vfcount; } ;
struct TYPE_4__ {TYPE_1__ arch; int /*<<< orphan*/  chip; } ;
struct adapter {TYPE_2__ params; } ;

/* Variables and functions */
 scalar_t__ CHELSIO_CHIP_VERSION (int /*<<< orphan*/ ) ; 
 scalar_t__ CHELSIO_T5 ; 
 int PCIE_FW_MASTER_M ; 
 int SGE_QBASE_DATA_REG_NUM ; 
 int cudbg_get_buff (struct cudbg_init*,struct cudbg_buffer*,int,struct cudbg_buffer*) ; 
 int /*<<< orphan*/  cudbg_read_sge_qbase_indirect_reg (struct adapter*,struct sge_qbase_reg_field*,int,int) ; 
 int cudbg_write_and_release_buff (struct cudbg_init*,struct cudbg_buffer*,struct cudbg_buffer*) ; 
 int /*<<< orphan*/  t4_read_indirect (struct adapter*,void*,void*,int /*<<< orphan*/ *,void*,void*) ; 
 void*** t5_sge_dbg_index_array ; 
 void** t6_sge_qbase_index_array ; 

int cudbg_collect_sge_indirect(struct cudbg_init *pdbg_init,
			       struct cudbg_buffer *dbg_buff,
			       struct cudbg_error *cudbg_err)
{
	struct adapter *padap = pdbg_init->adap;
	struct cudbg_buffer temp_buff = { 0 };
	struct sge_qbase_reg_field *sge_qbase;
	struct ireg_buf *ch_sge_dbg;
	int i, rc;

	rc = cudbg_get_buff(pdbg_init, dbg_buff,
			    sizeof(*ch_sge_dbg) * 2 + sizeof(*sge_qbase),
			    &temp_buff);
	if (rc)
		return rc;

	ch_sge_dbg = (struct ireg_buf *)temp_buff.data;
	for (i = 0; i < 2; i++) {
		struct ireg_field *sge_pio = &ch_sge_dbg->tp_pio;
		u32 *buff = ch_sge_dbg->outbuf;

		sge_pio->ireg_addr = t5_sge_dbg_index_array[i][0];
		sge_pio->ireg_data = t5_sge_dbg_index_array[i][1];
		sge_pio->ireg_local_offset = t5_sge_dbg_index_array[i][2];
		sge_pio->ireg_offset_range = t5_sge_dbg_index_array[i][3];
		t4_read_indirect(padap,
				 sge_pio->ireg_addr,
				 sge_pio->ireg_data,
				 buff,
				 sge_pio->ireg_offset_range,
				 sge_pio->ireg_local_offset);
		ch_sge_dbg++;
	}

	if (CHELSIO_CHIP_VERSION(padap->params.chip) > CHELSIO_T5) {
		sge_qbase = (struct sge_qbase_reg_field *)ch_sge_dbg;
		/* 1 addr reg SGE_QBASE_INDEX and 4 data reg
		 * SGE_QBASE_MAP[0-3]
		 */
		sge_qbase->reg_addr = t6_sge_qbase_index_array[0];
		for (i = 0; i < SGE_QBASE_DATA_REG_NUM; i++)
			sge_qbase->reg_data[i] =
				t6_sge_qbase_index_array[i + 1];

		for (i = 0; i <= PCIE_FW_MASTER_M; i++)
			cudbg_read_sge_qbase_indirect_reg(padap, sge_qbase,
							  i, true);

		for (i = 0; i < padap->params.arch.vfcount; i++)
			cudbg_read_sge_qbase_indirect_reg(padap, sge_qbase,
							  i, false);

		sge_qbase->vfcount = padap->params.arch.vfcount;
	}

	return cudbg_write_and_release_buff(pdbg_init, &temp_buff, dbg_buff);
}