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
 int /*<<< orphan*/  uasm_i_daddiu (int /*<<< orphan*/ **,unsigned int,unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  uasm_i_dsll (int /*<<< orphan*/ **,unsigned int,unsigned int,int) ; 
 int /*<<< orphan*/  uasm_i_dsll32 (int /*<<< orphan*/ **,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uasm_i_lui (int /*<<< orphan*/ **,unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  uasm_in_compat_space_p (long) ; 
 scalar_t__ uasm_rel_hi (long) ; 
 scalar_t__ uasm_rel_higher (long) ; 
 scalar_t__ uasm_rel_highest (long) ; 

void UASM_i_LA_mostly(u32 **buf, unsigned int rs, long addr)
{
	if (!uasm_in_compat_space_p(addr)) {
		uasm_i_lui(buf, rs, uasm_rel_highest(addr));
		if (uasm_rel_higher(addr))
			uasm_i_daddiu(buf, rs, rs, uasm_rel_higher(addr));
		if (uasm_rel_hi(addr)) {
			uasm_i_dsll(buf, rs, rs, 16);
			uasm_i_daddiu(buf, rs, rs,
					uasm_rel_hi(addr));
			uasm_i_dsll(buf, rs, rs, 16);
		} else
			uasm_i_dsll32(buf, rs, rs, 0);
	} else
		uasm_i_lui(buf, rs, uasm_rel_hi(addr));
}