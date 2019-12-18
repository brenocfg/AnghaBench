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
struct lm93_data {int* boost_hyst; int /*<<< orphan*/ * boost; } ;

/* Variables and functions */
 scalar_t__ LM93_TEMP_FROM_REG (int /*<<< orphan*/ ) ; 
 int LM93_TEMP_OFFSET_TO_REG (scalar_t__,int) ; 

__attribute__((used)) static u8 LM93_AUTO_BOOST_HYST_TO_REG(struct lm93_data *data, long hyst,
		int nr, int mode)
{
	u8 reg = LM93_TEMP_OFFSET_TO_REG(
			(LM93_TEMP_FROM_REG(data->boost[nr]) - hyst), mode);

	switch (nr) {
	case 0:
		reg = (data->boost_hyst[0] & 0xf0) | (reg & 0x0f);
		break;
	case 1:
		reg = (reg << 4 & 0xf0) | (data->boost_hyst[0] & 0x0f);
		break;
	case 2:
		reg = (data->boost_hyst[1] & 0xf0) | (reg & 0x0f);
		break;
	case 3:
	default:
		reg = (reg << 4 & 0xf0) | (data->boost_hyst[1] & 0x0f);
		break;
	}

	return reg;
}