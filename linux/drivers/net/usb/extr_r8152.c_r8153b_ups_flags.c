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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int speed_duplex; scalar_t__ ctap_short_off; scalar_t__ _250m_ckdiv; scalar_t__ eee_plloff_giga; scalar_t__ eee_plloff_100; scalar_t__ _10m_ckdiv; scalar_t__ eee_cmod_lv; scalar_t__ eee_ckdiv; scalar_t__ flow_control; scalar_t__ eee; scalar_t__ aldps; scalar_t__ green; } ;
struct r8152 {TYPE_1__ ups_info; } ;

/* Variables and functions */
#define  FORCE_100M_FULL 136 
#define  FORCE_100M_HALF 135 
#define  FORCE_10M_FULL 134 
#define  FORCE_10M_HALF 133 
 int /*<<< orphan*/  MCU_TYPE_USB ; 
#define  NWAY_1000M_FULL 132 
#define  NWAY_100M_FULL 131 
#define  NWAY_100M_HALF 130 
#define  NWAY_10M_FULL 129 
#define  NWAY_10M_HALF 128 
 int /*<<< orphan*/  UPS_FLAGS_250M_CKDIV ; 
 int /*<<< orphan*/  UPS_FLAGS_CTAP_SHORT_DIS ; 
 int /*<<< orphan*/  UPS_FLAGS_EEE_CMOD_LV_EN ; 
 int /*<<< orphan*/  UPS_FLAGS_EEE_PLLOFF_100 ; 
 int /*<<< orphan*/  UPS_FLAGS_EEE_PLLOFF_GIGA ; 
 int /*<<< orphan*/  UPS_FLAGS_EN_10M_CKDIV ; 
 int /*<<< orphan*/  UPS_FLAGS_EN_ALDPS ; 
 int /*<<< orphan*/  UPS_FLAGS_EN_EEE ; 
 int /*<<< orphan*/  UPS_FLAGS_EN_EEE_CKDIV ; 
 int /*<<< orphan*/  UPS_FLAGS_EN_FLOW_CTR ; 
 int /*<<< orphan*/  UPS_FLAGS_EN_GREEN ; 
 int /*<<< orphan*/  USB_UPS_FLAGS ; 
 int /*<<< orphan*/  ocp_write_dword (struct r8152*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ups_flags_speed (int) ; 

__attribute__((used)) static void r8153b_ups_flags(struct r8152 *tp)
{
	u32 ups_flags = 0;

	if (tp->ups_info.green)
		ups_flags |= UPS_FLAGS_EN_GREEN;

	if (tp->ups_info.aldps)
		ups_flags |= UPS_FLAGS_EN_ALDPS;

	if (tp->ups_info.eee)
		ups_flags |= UPS_FLAGS_EN_EEE;

	if (tp->ups_info.flow_control)
		ups_flags |= UPS_FLAGS_EN_FLOW_CTR;

	if (tp->ups_info.eee_ckdiv)
		ups_flags |= UPS_FLAGS_EN_EEE_CKDIV;

	if (tp->ups_info.eee_cmod_lv)
		ups_flags |= UPS_FLAGS_EEE_CMOD_LV_EN;

	if (tp->ups_info._10m_ckdiv)
		ups_flags |= UPS_FLAGS_EN_10M_CKDIV;

	if (tp->ups_info.eee_plloff_100)
		ups_flags |= UPS_FLAGS_EEE_PLLOFF_100;

	if (tp->ups_info.eee_plloff_giga)
		ups_flags |= UPS_FLAGS_EEE_PLLOFF_GIGA;

	if (tp->ups_info._250m_ckdiv)
		ups_flags |= UPS_FLAGS_250M_CKDIV;

	if (tp->ups_info.ctap_short_off)
		ups_flags |= UPS_FLAGS_CTAP_SHORT_DIS;

	switch (tp->ups_info.speed_duplex) {
	case NWAY_10M_HALF:
		ups_flags |= ups_flags_speed(1);
		break;
	case NWAY_10M_FULL:
		ups_flags |= ups_flags_speed(2);
		break;
	case NWAY_100M_HALF:
		ups_flags |= ups_flags_speed(3);
		break;
	case NWAY_100M_FULL:
		ups_flags |= ups_flags_speed(4);
		break;
	case NWAY_1000M_FULL:
		ups_flags |= ups_flags_speed(5);
		break;
	case FORCE_10M_HALF:
		ups_flags |= ups_flags_speed(6);
		break;
	case FORCE_10M_FULL:
		ups_flags |= ups_flags_speed(7);
		break;
	case FORCE_100M_HALF:
		ups_flags |= ups_flags_speed(8);
		break;
	case FORCE_100M_FULL:
		ups_flags |= ups_flags_speed(9);
		break;
	default:
		break;
	}

	ocp_write_dword(tp, MCU_TYPE_USB, USB_UPS_FLAGS, ups_flags);
}