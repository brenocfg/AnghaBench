#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  char u32 ;
struct voltagedomain {char (* read ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* write ) (char,int /*<<< orphan*/ ) ;TYPE_1__* pmic; struct omap_vp_instance* vp; } ;
struct omap_vp_instance {int /*<<< orphan*/  vpconfig; TYPE_2__* common; } ;
struct TYPE_4__ {char vpconfig_initvoltage_mask; char vpconfig_forceupdate; char vpconfig_initvdd; } ;
struct TYPE_3__ {char (* uv_to_vsel ) (char) ;} ;

/* Variables and functions */
 char __ffs (char) ; 
 char stub1 (char) ; 
 char stub2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 _vp_set_init_voltage(struct voltagedomain *voltdm, u32 volt)
{
	struct omap_vp_instance *vp = voltdm->vp;
	u32 vpconfig;
	char vsel;

	vsel = voltdm->pmic->uv_to_vsel(volt);

	vpconfig = voltdm->read(vp->vpconfig);
	vpconfig &= ~(vp->common->vpconfig_initvoltage_mask |
		      vp->common->vpconfig_forceupdate |
		      vp->common->vpconfig_initvdd);
	vpconfig |= vsel << __ffs(vp->common->vpconfig_initvoltage_mask);
	voltdm->write(vpconfig, vp->vpconfig);

	/* Trigger initVDD value copy to voltage processor */
	voltdm->write((vpconfig | vp->common->vpconfig_initvdd),
		       vp->vpconfig);

	/* Clear initVDD copy trigger bit */
	voltdm->write(vpconfig, vp->vpconfig);

	return vpconfig;
}