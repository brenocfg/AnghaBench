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

/* Variables and functions */
 int EINVAL ; 
 int GET_BITFIELD (int,int,int) ; 
 int /*<<< orphan*/  edac_dbg (int,char*,char*,int,int) ; 

__attribute__((used)) static int get_dimm_attr(u32 reg, int lobit, int hibit, int add, int minval,
			 int maxval, char *name)
{
	u32 val = GET_BITFIELD(reg, lobit, hibit);

	if (val < minval || val > maxval) {
		edac_dbg(2, "bad %s = %d (raw=%x)\n", name, val, reg);
		return -EINVAL;
	}
	return val + add;
}