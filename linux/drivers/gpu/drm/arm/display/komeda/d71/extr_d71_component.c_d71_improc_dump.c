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

__attribute__((used)) static void d71_improc_dump(struct komeda_component *c, struct seq_file *sf)
{
	u32 v[12], i;

	dump_block_header(sf, c->reg);

	get_values_from_reg(c->reg, 0x80, 2, v);
	seq_printf(sf, "IPS_INPUT_ID0:\t\t0x%X\n", v[0]);
	seq_printf(sf, "IPS_INPUT_ID1:\t\t0x%X\n", v[1]);

	get_values_from_reg(c->reg, 0xC0, 1, v);
	seq_printf(sf, "IPS_INFO:\t\t0x%X\n", v[0]);

	get_values_from_reg(c->reg, 0xD0, 3, v);
	seq_printf(sf, "IPS_CONTROL:\t\t0x%X\n", v[0]);
	seq_printf(sf, "IPS_SIZE:\t\t0x%X\n", v[1]);
	seq_printf(sf, "IPS_DEPTH:\t\t0x%X\n", v[2]);

	get_values_from_reg(c->reg, 0x130, 12, v);
	for (i = 0; i < 12; i++)
		seq_printf(sf, "IPS_RGB_RGB_COEFF%u:\t0x%X\n", i, v[i]);

	get_values_from_reg(c->reg, 0x170, 12, v);
	for (i = 0; i < 12; i++)
		seq_printf(sf, "IPS_RGB_YUV_COEFF%u:\t0x%X\n", i, v[i]);
}