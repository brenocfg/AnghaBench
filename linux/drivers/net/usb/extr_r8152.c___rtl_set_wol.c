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
typedef  int u32 ;
struct r8152 {TYPE_1__* udev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BWF_EN ; 
 int /*<<< orphan*/  CRWECR_CONFIG ; 
 int /*<<< orphan*/  CRWECR_NORAML ; 
 int LINK_ON_WAKE_EN ; 
 int MAGIC_EN ; 
 int /*<<< orphan*/  MCU_TYPE_PLA ; 
 int MWF_EN ; 
 int /*<<< orphan*/  PLA_CFG_WOL ; 
 int /*<<< orphan*/  PLA_CONFIG34 ; 
 int /*<<< orphan*/  PLA_CONFIG5 ; 
 int /*<<< orphan*/  PLA_CRWECR ; 
 int UWF_EN ; 
 int WAKE_ANY ; 
 int WAKE_BCAST ; 
 int WAKE_MAGIC ; 
 int WAKE_MCAST ; 
 int WAKE_PHY ; 
 int WAKE_UCAST ; 
 int /*<<< orphan*/  device_set_wakeup_enable (int /*<<< orphan*/ *,int) ; 
 int ocp_read_word (struct r8152*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocp_write_byte (struct r8152*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocp_write_word (struct r8152*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void __rtl_set_wol(struct r8152 *tp, u32 wolopts)
{
	u32 ocp_data;

	ocp_write_byte(tp, MCU_TYPE_PLA, PLA_CRWECR, CRWECR_CONFIG);

	ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_CONFIG34);
	ocp_data &= ~LINK_ON_WAKE_EN;
	if (wolopts & WAKE_PHY)
		ocp_data |= LINK_ON_WAKE_EN;
	ocp_write_word(tp, MCU_TYPE_PLA, PLA_CONFIG34, ocp_data);

	ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_CONFIG5);
	ocp_data &= ~(UWF_EN | BWF_EN | MWF_EN);
	if (wolopts & WAKE_UCAST)
		ocp_data |= UWF_EN;
	if (wolopts & WAKE_BCAST)
		ocp_data |= BWF_EN;
	if (wolopts & WAKE_MCAST)
		ocp_data |= MWF_EN;
	ocp_write_word(tp, MCU_TYPE_PLA, PLA_CONFIG5, ocp_data);

	ocp_write_byte(tp, MCU_TYPE_PLA, PLA_CRWECR, CRWECR_NORAML);

	ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_CFG_WOL);
	ocp_data &= ~MAGIC_EN;
	if (wolopts & WAKE_MAGIC)
		ocp_data |= MAGIC_EN;
	ocp_write_word(tp, MCU_TYPE_PLA, PLA_CFG_WOL, ocp_data);

	if (wolopts & WAKE_ANY)
		device_set_wakeup_enable(&tp->udev->dev, true);
	else
		device_set_wakeup_enable(&tp->udev->dev, false);
}