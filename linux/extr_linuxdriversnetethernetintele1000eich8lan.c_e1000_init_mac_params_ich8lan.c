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
struct TYPE_4__ {int /*<<< orphan*/  rar_get_count; int /*<<< orphan*/  setup_physical_interface; int /*<<< orphan*/  rar_set; int /*<<< orphan*/  led_off; int /*<<< orphan*/  led_on; int /*<<< orphan*/  cleanup_led; int /*<<< orphan*/  setup_led; int /*<<< orphan*/  id_led_init; int /*<<< orphan*/  check_mng_mode; int /*<<< orphan*/  blink_led; } ;
struct e1000_mac_info {int mta_reg_count; int type; int has_fwsm; int arc_subsystem_valid; int adaptive_ifs; TYPE_2__ ops; scalar_t__ rar_entry_count; } ;
struct TYPE_3__ {int /*<<< orphan*/  media_type; } ;
struct e1000_hw {TYPE_1__ phy; struct e1000_mac_info mac; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 scalar_t__ E1000_ICH_RAR_ENTRIES ; 
 scalar_t__ E1000_PCH2_RAR_ENTRIES ; 
 scalar_t__ E1000_PCH_LPT_RAR_ENTRIES ; 
 int /*<<< orphan*/  e1000_check_mng_mode_ich8lan ; 
 int /*<<< orphan*/  e1000_check_mng_mode_pchlan ; 
 int /*<<< orphan*/  e1000_cleanup_led_ich8lan ; 
 int /*<<< orphan*/  e1000_cleanup_led_pchlan ; 
#define  e1000_ich10lan 135 
#define  e1000_ich8lan 134 
#define  e1000_ich9lan 133 
 int /*<<< orphan*/  e1000_id_led_init_pchlan ; 
 int /*<<< orphan*/  e1000_led_off_ich8lan ; 
 int /*<<< orphan*/  e1000_led_off_pchlan ; 
 int /*<<< orphan*/  e1000_led_on_ich8lan ; 
 int /*<<< orphan*/  e1000_led_on_pchlan ; 
 int /*<<< orphan*/  e1000_media_type_copper ; 
#define  e1000_pch2lan 132 
#define  e1000_pch_cnp 131 
#define  e1000_pch_lpt 130 
#define  e1000_pch_spt 129 
#define  e1000_pchlan 128 
 int /*<<< orphan*/  e1000_rar_get_count_pch_lpt ; 
 int /*<<< orphan*/  e1000_rar_set_pch2lan ; 
 int /*<<< orphan*/  e1000_rar_set_pch_lpt ; 
 int /*<<< orphan*/  e1000_setup_copper_link_pch_lpt ; 
 int /*<<< orphan*/  e1000_setup_led_pchlan ; 
 int /*<<< orphan*/  e1000e_blink_led_generic ; 
 int /*<<< orphan*/  e1000e_id_led_init_generic ; 
 int /*<<< orphan*/  e1000e_set_kmrn_lock_loss_workaround_ich8lan (struct e1000_hw*,int) ; 
 int /*<<< orphan*/  e1000e_setup_led_generic ; 

__attribute__((used)) static s32 e1000_init_mac_params_ich8lan(struct e1000_hw *hw)
{
	struct e1000_mac_info *mac = &hw->mac;

	/* Set media type function pointer */
	hw->phy.media_type = e1000_media_type_copper;

	/* Set mta register count */
	mac->mta_reg_count = 32;
	/* Set rar entry count */
	mac->rar_entry_count = E1000_ICH_RAR_ENTRIES;
	if (mac->type == e1000_ich8lan)
		mac->rar_entry_count--;
	/* FWSM register */
	mac->has_fwsm = true;
	/* ARC subsystem not supported */
	mac->arc_subsystem_valid = false;
	/* Adaptive IFS supported */
	mac->adaptive_ifs = true;

	/* LED and other operations */
	switch (mac->type) {
	case e1000_ich8lan:
	case e1000_ich9lan:
	case e1000_ich10lan:
		/* check management mode */
		mac->ops.check_mng_mode = e1000_check_mng_mode_ich8lan;
		/* ID LED init */
		mac->ops.id_led_init = e1000e_id_led_init_generic;
		/* blink LED */
		mac->ops.blink_led = e1000e_blink_led_generic;
		/* setup LED */
		mac->ops.setup_led = e1000e_setup_led_generic;
		/* cleanup LED */
		mac->ops.cleanup_led = e1000_cleanup_led_ich8lan;
		/* turn on/off LED */
		mac->ops.led_on = e1000_led_on_ich8lan;
		mac->ops.led_off = e1000_led_off_ich8lan;
		break;
	case e1000_pch2lan:
		mac->rar_entry_count = E1000_PCH2_RAR_ENTRIES;
		mac->ops.rar_set = e1000_rar_set_pch2lan;
		/* fall-through */
	case e1000_pch_lpt:
	case e1000_pch_spt:
	case e1000_pch_cnp:
	case e1000_pchlan:
		/* check management mode */
		mac->ops.check_mng_mode = e1000_check_mng_mode_pchlan;
		/* ID LED init */
		mac->ops.id_led_init = e1000_id_led_init_pchlan;
		/* setup LED */
		mac->ops.setup_led = e1000_setup_led_pchlan;
		/* cleanup LED */
		mac->ops.cleanup_led = e1000_cleanup_led_pchlan;
		/* turn on/off LED */
		mac->ops.led_on = e1000_led_on_pchlan;
		mac->ops.led_off = e1000_led_off_pchlan;
		break;
	default:
		break;
	}

	if (mac->type >= e1000_pch_lpt) {
		mac->rar_entry_count = E1000_PCH_LPT_RAR_ENTRIES;
		mac->ops.rar_set = e1000_rar_set_pch_lpt;
		mac->ops.setup_physical_interface =
		    e1000_setup_copper_link_pch_lpt;
		mac->ops.rar_get_count = e1000_rar_get_count_pch_lpt;
	}

	/* Enable PCS Lock-loss workaround for ICH8 */
	if (mac->type == e1000_ich8lan)
		e1000e_set_kmrn_lock_loss_workaround_ich8lan(hw, true);

	return 0;
}