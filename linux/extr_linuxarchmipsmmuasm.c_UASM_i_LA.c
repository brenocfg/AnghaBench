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

/* Variables and functions */
 int /*<<< orphan*/  UASM_i_LA_mostly (int /*<<< orphan*/ **,unsigned int,long) ; 
 int /*<<< orphan*/  uasm_i_addiu (int /*<<< orphan*/ **,unsigned int,unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  uasm_i_daddiu (int /*<<< orphan*/ **,unsigned int,unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  uasm_in_compat_space_p (long) ; 
 scalar_t__ uasm_rel_lo (long) ; 

void UASM_i_LA(u32 **buf, unsigned int rs, long addr)
{
	UASM_i_LA_mostly(buf, rs, addr);
	if (uasm_rel_lo(addr)) {
		if (!uasm_in_compat_space_p(addr))
			uasm_i_daddiu(buf, rs, rs,
					uasm_rel_lo(addr));
		else
			uasm_i_addiu(buf, rs, rs,
					uasm_rel_lo(addr));
	}
}