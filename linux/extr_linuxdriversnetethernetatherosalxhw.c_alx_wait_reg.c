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
struct alx_hw {int dummy; } ;

/* Variables and functions */
 int ALX_SLD_MAX_TO ; 
 int alx_read_mem32 (struct alx_hw*,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static bool alx_wait_reg(struct alx_hw *hw, u32 reg, u32 wait, u32 *val)
{
	u32 read;
	int i;

	for (i = 0; i < ALX_SLD_MAX_TO; i++) {
		read = alx_read_mem32(hw, reg);
		if ((read & wait) == 0) {
			if (val)
				*val = read;
			return true;
		}
		mdelay(1);
	}

	return false;
}