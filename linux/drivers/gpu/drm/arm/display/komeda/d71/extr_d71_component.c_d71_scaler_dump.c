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
typedef  int /*<<< orphan*/  u32 ;
struct seq_file {int dummy; } ;
struct komeda_component {int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  dump_block_header (struct seq_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_values_from_reg (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void d71_scaler_dump(struct komeda_component *c, struct seq_file *sf)
{
	u32 v[9];

	dump_block_header(sf, c->reg);

	get_values_from_reg(c->reg, 0x80, 1, v);
	seq_printf(sf, "SC_INPUT_ID0:\t\t0x%X\n", v[0]);

	get_values_from_reg(c->reg, 0xD0, 1, v);
	seq_printf(sf, "SC_CONTROL:\t\t0x%X\n", v[0]);

	get_values_from_reg(c->reg, 0xDC, 9, v);
	seq_printf(sf, "SC_COEFFTAB:\t\t0x%X\n", v[0]);
	seq_printf(sf, "SC_IN_SIZE:\t\t0x%X\n", v[1]);
	seq_printf(sf, "SC_OUT_SIZE:\t\t0x%X\n", v[2]);
	seq_printf(sf, "SC_H_CROP:\t\t0x%X\n", v[3]);
	seq_printf(sf, "SC_V_CROP:\t\t0x%X\n", v[4]);
	seq_printf(sf, "SC_H_INIT_PH:\t\t0x%X\n", v[5]);
	seq_printf(sf, "SC_H_DELTA_PH:\t\t0x%X\n", v[6]);
	seq_printf(sf, "SC_V_INIT_PH:\t\t0x%X\n", v[7]);
	seq_printf(sf, "SC_V_DELTA_PH:\t\t0x%X\n", v[8]);
}