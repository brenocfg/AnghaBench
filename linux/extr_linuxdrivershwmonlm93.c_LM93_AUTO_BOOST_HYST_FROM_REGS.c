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
 int LM93_TEMP_FROM_REG (int /*<<< orphan*/ ) ; 
 int LM93_TEMP_OFFSET_FROM_REG (int,int) ; 

__attribute__((used)) static int LM93_AUTO_BOOST_HYST_FROM_REGS(struct lm93_data *data, int nr,
		int mode)
{
	u8 reg;

	switch (nr) {
	case 0:
		reg = data->boost_hyst[0] & 0x0f;
		break;
	case 1:
		reg = data->boost_hyst[0] >> 4 & 0x0f;
		break;
	case 2:
		reg = data->boost_hyst[1] & 0x0f;
		break;
	case 3:
	default:
		reg = data->boost_hyst[1] >> 4 & 0x0f;
		break;
	}

	return LM93_TEMP_FROM_REG(data->boost[nr]) -
			LM93_TEMP_OFFSET_FROM_REG(reg, mode);
}