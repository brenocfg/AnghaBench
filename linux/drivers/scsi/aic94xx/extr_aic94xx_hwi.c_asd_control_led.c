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
struct asd_ha_struct {int dummy; } ;

/* Variables and functions */
 int ASD_MAX_PHYS ; 
 int /*<<< orphan*/  GPIOCNFGR ; 
 int /*<<< orphan*/  GPIOOER ; 
 int asd_read_reg_dword (struct asd_ha_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asd_write_reg_dword (struct asd_ha_struct*,int /*<<< orphan*/ ,int) ; 

void asd_control_led(struct asd_ha_struct *asd_ha, int phy_id, int op)
{
	if (phy_id < ASD_MAX_PHYS) {
		u32 v;

		v = asd_read_reg_dword(asd_ha, GPIOOER);
		if (op)
			v |= (1 << phy_id);
		else
			v &= ~(1 << phy_id);
		asd_write_reg_dword(asd_ha, GPIOOER, v);

		v = asd_read_reg_dword(asd_ha, GPIOCNFGR);
		if (op)
			v |= (1 << phy_id);
		else
			v &= ~(1 << phy_id);
		asd_write_reg_dword(asd_ha, GPIOCNFGR, v);
	}
}