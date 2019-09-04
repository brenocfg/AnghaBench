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
typedef  size_t u8 ;
typedef  int u32 ;
struct qed_ptt {int dummy; } ;
struct dbg_tools_data {size_t chip_id; } ;
struct qed_hwfn {struct dbg_tools_data dbg_info; } ;
struct big_ram_defs {int* ram_size; int /*<<< orphan*/  data_reg_addr; int /*<<< orphan*/  addr_reg_addr; int /*<<< orphan*/  instance_name; int /*<<< orphan*/ * is_256b_bit_offset; int /*<<< orphan*/  is_256b_reg_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIG_RAM_NAME_LEN ; 
 int BIT (int /*<<< orphan*/ ) ; 
 int BRB_REG_BIG_RAM_DATA_SIZE ; 
 int BYTES_TO_DWORDS (int /*<<< orphan*/ ) ; 
 int DIV_ROUND_UP (int,int) ; 
 int /*<<< orphan*/  SPLIT_TYPE_NONE ; 
 int qed_grc_dump_addr_range (struct qed_hwfn*,struct qed_ptt*,int*,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int qed_grc_dump_mem_hdr (struct qed_hwfn*,int*,int,char*,int /*<<< orphan*/ ,int,int,int,char*,int,int /*<<< orphan*/ ) ; 
 int qed_rd (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qed_wr (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ ,int) ; 
 struct big_ram_defs* s_big_ram_defs ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 qed_grc_dump_big_ram(struct qed_hwfn *p_hwfn,
				struct qed_ptt *p_ptt,
				u32 *dump_buf, bool dump, u8 big_ram_id)
{
	struct dbg_tools_data *dev_data = &p_hwfn->dbg_info;
	u32 block_size, ram_size, offset = 0, reg_val, i;
	char mem_name[12] = "???_BIG_RAM";
	char type_name[8] = "???_RAM";
	struct big_ram_defs *big_ram;

	big_ram = &s_big_ram_defs[big_ram_id];
	ram_size = big_ram->ram_size[dev_data->chip_id];

	reg_val = qed_rd(p_hwfn, p_ptt, big_ram->is_256b_reg_addr);
	block_size = reg_val &
		     BIT(big_ram->is_256b_bit_offset[dev_data->chip_id]) ? 256
									 : 128;

	strncpy(type_name, big_ram->instance_name, BIG_RAM_NAME_LEN);
	strncpy(mem_name, big_ram->instance_name, BIG_RAM_NAME_LEN);

	/* Dump memory header */
	offset += qed_grc_dump_mem_hdr(p_hwfn,
				       dump_buf + offset,
				       dump,
				       mem_name,
				       0,
				       ram_size,
				       block_size * 8,
				       false, type_name, false, 0);

	/* Read and dump Big RAM data */
	if (!dump)
		return offset + ram_size;

	/* Dump Big RAM */
	for (i = 0; i < DIV_ROUND_UP(ram_size, BRB_REG_BIG_RAM_DATA_SIZE);
	     i++) {
		u32 addr, len;

		qed_wr(p_hwfn, p_ptt, big_ram->addr_reg_addr, i);
		addr = BYTES_TO_DWORDS(big_ram->data_reg_addr);
		len = BRB_REG_BIG_RAM_DATA_SIZE;
		offset += qed_grc_dump_addr_range(p_hwfn,
						  p_ptt,
						  dump_buf + offset,
						  dump,
						  addr,
						  len,
						  false, SPLIT_TYPE_NONE, 0);
	}

	return offset;
}