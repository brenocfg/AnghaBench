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
typedef  int /*<<< orphan*/  u32 ;
struct r8152 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EEEP_CR_EEEP_TX ; 
 int /*<<< orphan*/  MCU_TYPE_PLA ; 
 int /*<<< orphan*/  PLA_EEEP_CR ; 
 int _10bps ; 
 int /*<<< orphan*/  ocp_read_word (struct r8152*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocp_write_word (struct r8152*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rtl8152_get_speed (struct r8152*) ; 

__attribute__((used)) static void rtl_set_eee_plus(struct r8152 *tp)
{
	u32 ocp_data;
	u8 speed;

	speed = rtl8152_get_speed(tp);
	if (speed & _10bps) {
		ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_EEEP_CR);
		ocp_data |= EEEP_CR_EEEP_TX;
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_EEEP_CR, ocp_data);
	} else {
		ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_EEEP_CR);
		ocp_data &= ~EEEP_CR_EEEP_TX;
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_EEEP_CR, ocp_data);
	}
}