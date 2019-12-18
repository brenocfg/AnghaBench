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
typedef  int /*<<< orphan*/  u32 ;
struct r8152 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LINK_CHANGE_FLAG ; 
 int /*<<< orphan*/  LINK_CHG_EVENT ; 
 int /*<<< orphan*/  MCU_TYPE_PLA ; 
 int /*<<< orphan*/  PLA_EXTRA_STATUS ; 
 int /*<<< orphan*/  PLA_INDICATE_FALG ; 
 int /*<<< orphan*/  PLA_SUSPEND_FLAG ; 
 int /*<<< orphan*/  UPCOMING_RUNTIME_D3 ; 
 int /*<<< orphan*/  ocp_read_byte (struct r8152*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocp_read_word (struct r8152*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocp_write_byte (struct r8152*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocp_write_word (struct r8152*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void r8153_queue_wake(struct r8152 *tp, bool enable)
{
	u32 ocp_data;

	ocp_data = ocp_read_byte(tp, MCU_TYPE_PLA, PLA_INDICATE_FALG);
	if (enable)
		ocp_data |= UPCOMING_RUNTIME_D3;
	else
		ocp_data &= ~UPCOMING_RUNTIME_D3;
	ocp_write_byte(tp, MCU_TYPE_PLA, PLA_INDICATE_FALG, ocp_data);

	ocp_data = ocp_read_byte(tp, MCU_TYPE_PLA, PLA_SUSPEND_FLAG);
	ocp_data &= ~LINK_CHG_EVENT;
	ocp_write_byte(tp, MCU_TYPE_PLA, PLA_SUSPEND_FLAG, ocp_data);

	ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_EXTRA_STATUS);
	ocp_data &= ~LINK_CHANGE_FLAG;
	ocp_write_word(tp, MCU_TYPE_PLA, PLA_EXTRA_STATUS, ocp_data);
}