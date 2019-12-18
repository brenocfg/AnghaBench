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
typedef  int u32 ;
struct seq_file {int dummy; } ;
struct komeda_component {int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  dump_block_header (struct seq_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_values_from_reg (int /*<<< orphan*/ ,int,int,int*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int,...) ; 

__attribute__((used)) static void d71_compiz_dump(struct komeda_component *c, struct seq_file *sf)
{
	u32 v[8], i;

	dump_block_header(sf, c->reg);

	get_values_from_reg(c->reg, 0x80, 5, v);
	for (i = 0; i < 5; i++)
		seq_printf(sf, "CU_INPUT_ID%u:\t\t0x%X\n", i, v[i]);

	get_values_from_reg(c->reg, 0xA0, 5, v);
	seq_printf(sf, "CU_IRQ_RAW_STATUS:\t0x%X\n", v[0]);
	seq_printf(sf, "CU_IRQ_CLEAR:\t\t0x%X\n", v[1]);
	seq_printf(sf, "CU_IRQ_MASK:\t\t0x%X\n", v[2]);
	seq_printf(sf, "CU_IRQ_STATUS:\t\t0x%X\n", v[3]);
	seq_printf(sf, "CU_STATUS:\t\t0x%X\n", v[4]);

	get_values_from_reg(c->reg, 0xD0, 2, v);
	seq_printf(sf, "CU_CONTROL:\t\t0x%X\n", v[0]);
	seq_printf(sf, "CU_SIZE:\t\t0x%X\n", v[1]);

	get_values_from_reg(c->reg, 0xDC, 1, v);
	seq_printf(sf, "CU_BG_COLOR:\t\t0x%X\n", v[0]);

	for (i = 0, v[4] = 0xE0; i < 5; i++, v[4] += 0x10) {
		get_values_from_reg(c->reg, v[4], 3, v);
		seq_printf(sf, "CU_INPUT%u_SIZE:\t\t0x%X\n", i, v[0]);
		seq_printf(sf, "CU_INPUT%u_OFFSET:\t0x%X\n", i, v[1]);
		seq_printf(sf, "CU_INPUT%u_CONTROL:\t0x%X\n", i, v[2]);
	}

	get_values_from_reg(c->reg, 0x130, 2, v);
	seq_printf(sf, "CU_USER_LOW:\t\t0x%X\n", v[0]);
	seq_printf(sf, "CU_USER_HIGH:\t\t0x%X\n", v[1]);
}