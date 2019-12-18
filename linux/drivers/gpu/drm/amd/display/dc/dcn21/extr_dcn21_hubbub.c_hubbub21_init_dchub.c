#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct hubbub {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  agp_base; int /*<<< orphan*/  agp_top; int /*<<< orphan*/  agp_bot; int /*<<< orphan*/  fb_offset; int /*<<< orphan*/  fb_top; int /*<<< orphan*/  fb_base; } ;
struct dcn_hubbub_phys_addr_config {TYPE_1__ system_aperture; } ;
struct dcn20_hubbub {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AGP_BASE ; 
 int /*<<< orphan*/  AGP_BOT ; 
 int /*<<< orphan*/  AGP_TOP ; 
 int /*<<< orphan*/  DCN_VM_AGP_BASE ; 
 int /*<<< orphan*/  DCN_VM_AGP_BOT ; 
 int /*<<< orphan*/  DCN_VM_AGP_TOP ; 
 int /*<<< orphan*/  DCN_VM_FB_LOCATION_BASE ; 
 int /*<<< orphan*/  DCN_VM_FB_LOCATION_TOP ; 
 int /*<<< orphan*/  DCN_VM_FB_OFFSET ; 
 int /*<<< orphan*/  FB_BASE ; 
 int /*<<< orphan*/  FB_OFFSET ; 
 int /*<<< orphan*/  FB_TOP ; 
 int NUM_VMID ; 
 int /*<<< orphan*/  REG_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dcn20_hubbub* TO_DCN20_HUBBUB (struct hubbub*) ; 
 int /*<<< orphan*/  dcn21_dchvm_init (struct hubbub*) ; 

__attribute__((used)) static int hubbub21_init_dchub(struct hubbub *hubbub,
		struct dcn_hubbub_phys_addr_config *pa_config)
{
	struct dcn20_hubbub *hubbub1 = TO_DCN20_HUBBUB(hubbub);

	REG_SET(DCN_VM_FB_LOCATION_BASE, 0,
		FB_BASE, pa_config->system_aperture.fb_base);
	REG_SET(DCN_VM_FB_LOCATION_TOP, 0,
			FB_TOP, pa_config->system_aperture.fb_top);
	REG_SET(DCN_VM_FB_OFFSET, 0,
			FB_OFFSET, pa_config->system_aperture.fb_offset);
	REG_SET(DCN_VM_AGP_BOT, 0,
			AGP_BOT, pa_config->system_aperture.agp_bot);
	REG_SET(DCN_VM_AGP_TOP, 0,
			AGP_TOP, pa_config->system_aperture.agp_top);
	REG_SET(DCN_VM_AGP_BASE, 0,
			AGP_BASE, pa_config->system_aperture.agp_base);

	dcn21_dchvm_init(hubbub);

	return NUM_VMID;
}