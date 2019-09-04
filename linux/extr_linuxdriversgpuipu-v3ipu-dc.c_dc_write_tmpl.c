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
struct ipu_dc_priv {scalar_t__ dc_tmpl_reg; } ;
struct ipu_dc {struct ipu_dc_priv* priv; } ;

/* Variables and functions */
 int WCLK ; 
 int WRG ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void dc_write_tmpl(struct ipu_dc *dc, int word, u32 opcode, u32 operand,
		int map, int wave, int glue, int sync, int stop)
{
	struct ipu_dc_priv *priv = dc->priv;
	u32 reg1, reg2;

	if (opcode == WCLK) {
		reg1 = (operand << 20) & 0xfff00000;
		reg2 = operand >> 12 | opcode << 1 | stop << 9;
	} else if (opcode == WRG) {
		reg1 = sync | glue << 4 | ++wave << 11 | ((operand << 15) & 0xffff8000);
		reg2 = operand >> 17 | opcode << 7 | stop << 9;
	} else {
		reg1 = sync | glue << 4 | ++wave << 11 | ++map << 15 | ((operand << 20) & 0xfff00000);
		reg2 = operand >> 12 | opcode << 4 | stop << 9;
	}
	writel(reg1, priv->dc_tmpl_reg + word * 8);
	writel(reg2, priv->dc_tmpl_reg + word * 8 + 4);
}