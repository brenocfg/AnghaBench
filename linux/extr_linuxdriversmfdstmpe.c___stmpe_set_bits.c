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
struct stmpe {int dummy; } ;

/* Variables and functions */
 int __stmpe_reg_read (struct stmpe*,int) ; 
 int __stmpe_reg_write (struct stmpe*,int,int) ; 

__attribute__((used)) static int __stmpe_set_bits(struct stmpe *stmpe, u8 reg, u8 mask, u8 val)
{
	int ret;

	ret = __stmpe_reg_read(stmpe, reg);
	if (ret < 0)
		return ret;

	ret &= ~mask;
	ret |= val;

	return __stmpe_reg_write(stmpe, reg, ret);
}