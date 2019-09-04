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
typedef  size_t u32 ;
struct sge_qbase_reg_field {size_t** pf_data_value; size_t** vf_data_value; int /*<<< orphan*/ * reg_data; int /*<<< orphan*/  reg_addr; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 size_t SGE_QBASE_DATA_REG_NUM ; 
 size_t t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_write_reg (struct adapter*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static void cudbg_read_sge_qbase_indirect_reg(struct adapter *padap,
					      struct sge_qbase_reg_field *qbase,
					      u32 func, bool is_pf)
{
	u32 *buff, i;

	if (is_pf) {
		buff = qbase->pf_data_value[func];
	} else {
		buff = qbase->vf_data_value[func];
		/* In SGE_QBASE_INDEX,
		 * Entries 0->7 are PF0->7, Entries 8->263 are VFID0->256.
		 */
		func += 8;
	}

	t4_write_reg(padap, qbase->reg_addr, func);
	for (i = 0; i < SGE_QBASE_DATA_REG_NUM; i++, buff++)
		*buff = t4_read_reg(padap, qbase->reg_data[i]);
}