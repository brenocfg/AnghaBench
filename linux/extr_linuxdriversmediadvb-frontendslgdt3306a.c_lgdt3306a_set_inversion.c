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
struct lgdt3306a_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dbg_info (char*,int) ; 
 int lgdt3306a_set_reg_bit (struct lgdt3306a_state*,int,int,int) ; 

__attribute__((used)) static int lgdt3306a_set_inversion(struct lgdt3306a_state *state,
				       int inversion)
{
	int ret;

	dbg_info("(%d)\n", inversion);

	ret = lgdt3306a_set_reg_bit(state, 0x0002, 2, inversion ? 1 : 0);
	return ret;
}