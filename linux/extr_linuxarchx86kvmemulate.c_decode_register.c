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
typedef  int u8 ;
struct x86_emulate_ctxt {scalar_t__ rex_prefix; } ;

/* Variables and functions */
 void* reg_rmw (struct x86_emulate_ctxt*,int) ; 

__attribute__((used)) static void *decode_register(struct x86_emulate_ctxt *ctxt, u8 modrm_reg,
			     int byteop)
{
	void *p;
	int highbyte_regs = (ctxt->rex_prefix == 0) && byteop;

	if (highbyte_regs && modrm_reg >= 4 && modrm_reg < 8)
		p = (unsigned char *)reg_rmw(ctxt, modrm_reg & 3) + 1;
	else
		p = reg_rmw(ctxt, modrm_reg);
	return p;
}