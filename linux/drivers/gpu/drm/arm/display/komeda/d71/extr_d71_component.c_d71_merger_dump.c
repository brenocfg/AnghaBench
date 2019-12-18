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
 int /*<<< orphan*/  BLK_CONTROL ; 
 int /*<<< orphan*/  MG_INPUT_ID0 ; 
 int /*<<< orphan*/  MG_INPUT_ID1 ; 
 int /*<<< orphan*/  MG_SIZE ; 
 int /*<<< orphan*/  dump_block_header (struct seq_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_values_from_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void d71_merger_dump(struct komeda_component *c, struct seq_file *sf)
{
	u32 v;

	dump_block_header(sf, c->reg);

	get_values_from_reg(c->reg, MG_INPUT_ID0, 1, &v);
	seq_printf(sf, "MG_INPUT_ID0:\t\t0x%X\n", v);

	get_values_from_reg(c->reg, MG_INPUT_ID1, 1, &v);
	seq_printf(sf, "MG_INPUT_ID1:\t\t0x%X\n", v);

	get_values_from_reg(c->reg, BLK_CONTROL, 1, &v);
	seq_printf(sf, "MG_CONTROL:\t\t0x%X\n", v);

	get_values_from_reg(c->reg, MG_SIZE, 1, &v);
	seq_printf(sf, "MG_SIZE:\t\t0x%X\n", v);
}