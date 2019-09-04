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
typedef  int u64 ;
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  do_div (int,int) ; 

__attribute__((used)) static unsigned long roclk_calc_rate(unsigned long parent_rate,
				     u32 rodiv, u32 rotrim)
{
	u64 rate64;

	/* fout = fin / [2 * {div + (trim / 512)}]
	 *	= fin * 512 / [1024 * div + 2 * trim]
	 *	= fin * 256 / (512 * div + trim)
	 *	= (fin << 8) / ((div << 9) + trim)
	 */
	if (rotrim) {
		rodiv = (rodiv << 9) + rotrim;
		rate64 = parent_rate;
		rate64 <<= 8;
		do_div(rate64, rodiv);
	} else if (rodiv) {
		rate64 = parent_rate / (rodiv << 1);
	} else {
		rate64 = parent_rate;
	}
	return rate64;
}