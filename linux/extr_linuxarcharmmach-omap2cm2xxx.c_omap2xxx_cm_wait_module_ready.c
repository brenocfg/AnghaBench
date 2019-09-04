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
typedef  int u32 ;
typedef  int u16 ;
typedef  int /*<<< orphan*/  s16 ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int EBUSY ; 
 int EINVAL ; 
 int MAX_MODULE_READY_TIME ; 
 int omap2_cm_read_mod_reg (int /*<<< orphan*/ ,int) ; 
 int* omap2xxx_cm_idlest_offs ; 
 int /*<<< orphan*/  omap_test_timeout (int,int,int) ; 

int omap2xxx_cm_wait_module_ready(u8 part, s16 prcm_mod, u16 idlest_id,
				  u8 idlest_shift)
{
	int ena = 0, i = 0;
	u8 cm_idlest_reg;
	u32 mask;

	if (!idlest_id || (idlest_id > ARRAY_SIZE(omap2xxx_cm_idlest_offs)))
		return -EINVAL;

	cm_idlest_reg = omap2xxx_cm_idlest_offs[idlest_id - 1];

	mask = 1 << idlest_shift;
	ena = mask;

	omap_test_timeout(((omap2_cm_read_mod_reg(prcm_mod, cm_idlest_reg) &
			    mask) == ena), MAX_MODULE_READY_TIME, i);

	return (i < MAX_MODULE_READY_TIME) ? 0 : -EBUSY;
}