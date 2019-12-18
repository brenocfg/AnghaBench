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
typedef  int uint32_t ;
struct qla_hw_data {int fw_memory_size; int /*<<< orphan*/  fw_dump_cap_flags; } ;

/* Variables and functions */
 int QLA_SUCCESS ; 
 int /*<<< orphan*/  RISC_EXT_MEM_DUMP_CMPL ; 
 int /*<<< orphan*/  RISC_SRAM_DUMP_CMPL ; 
 int qla24xx_dump_ram (struct qla_hw_data*,int,void*,int,void**) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
qla24xx_dump_memory(struct qla_hw_data *ha, uint32_t *code_ram,
    uint32_t cram_size, void **nxt)
{
	int rval;

	/* Code RAM. */
	rval = qla24xx_dump_ram(ha, 0x20000, code_ram, cram_size / 4, nxt);
	if (rval != QLA_SUCCESS)
		return rval;

	set_bit(RISC_SRAM_DUMP_CMPL, &ha->fw_dump_cap_flags);

	/* External Memory. */
	rval = qla24xx_dump_ram(ha, 0x100000, *nxt,
	    ha->fw_memory_size - 0x100000 + 1, nxt);
	if (rval == QLA_SUCCESS)
		set_bit(RISC_EXT_MEM_DUMP_CMPL, &ha->fw_dump_cap_flags);

	return rval;
}