#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int quad_part; } ;
struct TYPE_5__ {int quad_part; } ;
struct TYPE_7__ {int quad_part; } ;
struct vm_system_aperture_param {TYPE_2__ sys_high; TYPE_1__ sys_low; TYPE_3__ sys_default; } ;
struct hubp {int dummy; } ;
struct dcn21_hubp {int dummy; } ;
struct TYPE_8__ {int quad_part; } ;
typedef  TYPE_4__ PHYSICAL_ADDRESS_LOC ;

/* Variables and functions */
 int /*<<< orphan*/  DCN_VM_MX_L1_TLB_CNTL ; 
 int /*<<< orphan*/  DCN_VM_SYSTEM_APERTURE_HIGH_ADDR ; 
 int /*<<< orphan*/  DCN_VM_SYSTEM_APERTURE_LOW_ADDR ; 
 int /*<<< orphan*/  ENABLE_L1_TLB ; 
 int /*<<< orphan*/  MC_VM_SYSTEM_APERTURE_HIGH_ADDR ; 
 int /*<<< orphan*/  MC_VM_SYSTEM_APERTURE_LOW_ADDR ; 
 int /*<<< orphan*/  REG_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_SET_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SYSTEM_ACCESS_MODE ; 
 struct dcn21_hubp* TO_DCN21_HUBP (struct hubp*) ; 

void hubp21_set_vm_system_aperture_settings(struct hubp *hubp,
		struct vm_system_aperture_param *apt)
{
	struct dcn21_hubp *hubp21 = TO_DCN21_HUBP(hubp);

	PHYSICAL_ADDRESS_LOC mc_vm_apt_default;
	PHYSICAL_ADDRESS_LOC mc_vm_apt_low;
	PHYSICAL_ADDRESS_LOC mc_vm_apt_high;

	// The format of default addr is 48:12 of the 48 bit addr
	mc_vm_apt_default.quad_part = apt->sys_default.quad_part >> 12;

	// The format of high/low are 48:18 of the 48 bit addr
	mc_vm_apt_low.quad_part = apt->sys_low.quad_part >> 18;
	mc_vm_apt_high.quad_part = apt->sys_high.quad_part >> 18;

	REG_SET(DCN_VM_SYSTEM_APERTURE_LOW_ADDR, 0,
			MC_VM_SYSTEM_APERTURE_LOW_ADDR, mc_vm_apt_low.quad_part);

	REG_SET(DCN_VM_SYSTEM_APERTURE_HIGH_ADDR, 0,
			MC_VM_SYSTEM_APERTURE_HIGH_ADDR, mc_vm_apt_high.quad_part);

	REG_SET_2(DCN_VM_MX_L1_TLB_CNTL, 0,
			ENABLE_L1_TLB, 1,
			SYSTEM_ACCESS_MODE, 0x3);
}