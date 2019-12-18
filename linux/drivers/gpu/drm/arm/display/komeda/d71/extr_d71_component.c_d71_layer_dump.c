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
 int LAYER_INFO ; 
 int LAYER_RGB_RGB_COEFF0 ; 
 int L_INFO_CM ; 
 int /*<<< orphan*/  dump_block_header (struct seq_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_values_from_reg (int /*<<< orphan*/ ,int,int,int*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 

__attribute__((used)) static void d71_layer_dump(struct komeda_component *c, struct seq_file *sf)
{
	u32 v[15], i;
	bool rich, rgb2rgb;
	char *prefix;

	get_values_from_reg(c->reg, LAYER_INFO, 1, &v[14]);
	if (v[14] & 0x1) {
		rich = true;
		prefix = "LR_";
	} else {
		rich = false;
		prefix = "LS_";
	}

	rgb2rgb = !!(v[14] & L_INFO_CM);

	dump_block_header(sf, c->reg);

	seq_printf(sf, "%sLAYER_INFO:\t\t0x%X\n", prefix, v[14]);

	get_values_from_reg(c->reg, 0xD0, 1, v);
	seq_printf(sf, "%sCONTROL:\t\t0x%X\n", prefix, v[0]);
	if (rich) {
		get_values_from_reg(c->reg, 0xD4, 1, v);
		seq_printf(sf, "LR_RICH_CONTROL:\t0x%X\n", v[0]);
	}
	get_values_from_reg(c->reg, 0xD8, 4, v);
	seq_printf(sf, "%sFORMAT:\t\t0x%X\n", prefix, v[0]);
	seq_printf(sf, "%sIT_COEFFTAB:\t\t0x%X\n", prefix, v[1]);
	seq_printf(sf, "%sIN_SIZE:\t\t0x%X\n", prefix, v[2]);
	seq_printf(sf, "%sPALPHA:\t\t0x%X\n", prefix, v[3]);

	get_values_from_reg(c->reg, 0x100, 3, v);
	seq_printf(sf, "%sP0_PTR_LOW:\t\t0x%X\n", prefix, v[0]);
	seq_printf(sf, "%sP0_PTR_HIGH:\t\t0x%X\n", prefix, v[1]);
	seq_printf(sf, "%sP0_STRIDE:\t\t0x%X\n", prefix, v[2]);

	get_values_from_reg(c->reg, 0x110, 2, v);
	seq_printf(sf, "%sP1_PTR_LOW:\t\t0x%X\n", prefix, v[0]);
	seq_printf(sf, "%sP1_PTR_HIGH:\t\t0x%X\n", prefix, v[1]);
	if (rich) {
		get_values_from_reg(c->reg, 0x118, 1, v);
		seq_printf(sf, "LR_P1_STRIDE:\t\t0x%X\n", v[0]);

		get_values_from_reg(c->reg, 0x120, 2, v);
		seq_printf(sf, "LR_P2_PTR_LOW:\t\t0x%X\n", v[0]);
		seq_printf(sf, "LR_P2_PTR_HIGH:\t\t0x%X\n", v[1]);

		get_values_from_reg(c->reg, 0x130, 12, v);
		for (i = 0; i < 12; i++)
			seq_printf(sf, "LR_YUV_RGB_COEFF%u:\t0x%X\n", i, v[i]);
	}

	if (rgb2rgb) {
		get_values_from_reg(c->reg, LAYER_RGB_RGB_COEFF0, 12, v);
		for (i = 0; i < 12; i++)
			seq_printf(sf, "LS_RGB_RGB_COEFF%u:\t0x%X\n", i, v[i]);
	}

	get_values_from_reg(c->reg, 0x160, 3, v);
	seq_printf(sf, "%sAD_CONTROL:\t\t0x%X\n", prefix, v[0]);
	seq_printf(sf, "%sAD_H_CROP:\t\t0x%X\n", prefix, v[1]);
	seq_printf(sf, "%sAD_V_CROP:\t\t0x%X\n", prefix, v[2]);
}