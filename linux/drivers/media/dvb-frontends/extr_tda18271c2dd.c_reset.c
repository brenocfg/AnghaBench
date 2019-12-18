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
struct tda_state {int m_SettlingTime; int m_IFLevelAnalog; int m_IFLevelDigital; int m_IFLevelDVBC; int m_IFLevelDVBT; int m_EP4; int m_EP3_Standby; int m_bMaster; int m_bFMInput; scalar_t__ m_Frequency; } ;

/* Variables and functions */

__attribute__((used)) static void reset(struct tda_state *state)
{
	u32   ulIFLevelAnalog = 0;
	u32   ulIFLevelDigital = 2;
	u32   ulIFLevelDVBC = 7;
	u32   ulIFLevelDVBT = 6;
	u32   ulXTOut = 0;
	u32   ulStandbyMode = 0x06;    /* Send in stdb, but leave osc on */
	u32   ulSlave = 0;
	u32   ulFMInput = 0;
	u32   ulSettlingTime = 100;

	state->m_Frequency         = 0;
	state->m_SettlingTime = 100;
	state->m_IFLevelAnalog = (ulIFLevelAnalog & 0x07) << 2;
	state->m_IFLevelDigital = (ulIFLevelDigital & 0x07) << 2;
	state->m_IFLevelDVBC = (ulIFLevelDVBC & 0x07) << 2;
	state->m_IFLevelDVBT = (ulIFLevelDVBT & 0x07) << 2;

	state->m_EP4 = 0x20;
	if (ulXTOut != 0)
		state->m_EP4 |= 0x40;

	state->m_EP3_Standby = ((ulStandbyMode & 0x07) << 5) | 0x0F;
	state->m_bMaster = (ulSlave == 0);

	state->m_SettlingTime = ulSettlingTime;

	state->m_bFMInput = (ulFMInput == 2);
}