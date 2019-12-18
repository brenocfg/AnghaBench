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
typedef  int s8 ;

/* Variables and functions */
#define  DESC_RATE11M 175 
#define  DESC_RATE12M 174 
#define  DESC_RATE18M 173 
#define  DESC_RATE1M 172 
#define  DESC_RATE24M 171 
#define  DESC_RATE2M 170 
#define  DESC_RATE36M 169 
#define  DESC_RATE48M 168 
#define  DESC_RATE54M 167 
#define  DESC_RATE5_5M 166 
#define  DESC_RATE6M 165 
#define  DESC_RATE9M 164 
#define  DESC_RATEMCS0 163 
#define  DESC_RATEMCS1 162 
#define  DESC_RATEMCS10 161 
#define  DESC_RATEMCS11 160 
#define  DESC_RATEMCS12 159 
#define  DESC_RATEMCS13 158 
#define  DESC_RATEMCS14 157 
#define  DESC_RATEMCS15 156 
#define  DESC_RATEMCS2 155 
#define  DESC_RATEMCS3 154 
#define  DESC_RATEMCS4 153 
#define  DESC_RATEMCS5 152 
#define  DESC_RATEMCS6 151 
#define  DESC_RATEMCS7 150 
#define  DESC_RATEMCS8 149 
#define  DESC_RATEMCS9 148 
#define  DESC_RATEVHT1SS_MCS0 147 
#define  DESC_RATEVHT1SS_MCS1 146 
#define  DESC_RATEVHT1SS_MCS2 145 
#define  DESC_RATEVHT1SS_MCS3 144 
#define  DESC_RATEVHT1SS_MCS4 143 
#define  DESC_RATEVHT1SS_MCS5 142 
#define  DESC_RATEVHT1SS_MCS6 141 
#define  DESC_RATEVHT1SS_MCS7 140 
#define  DESC_RATEVHT1SS_MCS8 139 
#define  DESC_RATEVHT1SS_MCS9 138 
#define  DESC_RATEVHT2SS_MCS0 137 
#define  DESC_RATEVHT2SS_MCS1 136 
#define  DESC_RATEVHT2SS_MCS2 135 
#define  DESC_RATEVHT2SS_MCS3 134 
#define  DESC_RATEVHT2SS_MCS4 133 
#define  DESC_RATEVHT2SS_MCS5 132 
#define  DESC_RATEVHT2SS_MCS6 131 
#define  DESC_RATEVHT2SS_MCS7 130 
#define  DESC_RATEVHT2SS_MCS8 129 
#define  DESC_RATEVHT2SS_MCS9 128 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 

__attribute__((used)) static s8 _rtl8821ae_phy_get_ratesection_intxpower_byrate(u8 path, u8 rate)
{
	s8 rate_section = 0;
	switch (rate) {
	case DESC_RATE1M:
	case DESC_RATE2M:
	case DESC_RATE5_5M:
	case DESC_RATE11M:
		rate_section = 0;
		break;
	case DESC_RATE6M:
	case DESC_RATE9M:
	case DESC_RATE12M:
	case DESC_RATE18M:
		rate_section = 1;
		break;
	case DESC_RATE24M:
	case DESC_RATE36M:
	case DESC_RATE48M:
	case DESC_RATE54M:
		rate_section = 2;
		break;
	case DESC_RATEMCS0:
	case DESC_RATEMCS1:
	case DESC_RATEMCS2:
	case DESC_RATEMCS3:
		rate_section = 3;
		break;
	case DESC_RATEMCS4:
	case DESC_RATEMCS5:
	case DESC_RATEMCS6:
	case DESC_RATEMCS7:
		rate_section = 4;
		break;
	case DESC_RATEMCS8:
	case DESC_RATEMCS9:
	case DESC_RATEMCS10:
	case DESC_RATEMCS11:
		rate_section = 5;
		break;
	case DESC_RATEMCS12:
	case DESC_RATEMCS13:
	case DESC_RATEMCS14:
	case DESC_RATEMCS15:
		rate_section = 6;
		break;
	case DESC_RATEVHT1SS_MCS0:
	case DESC_RATEVHT1SS_MCS1:
	case DESC_RATEVHT1SS_MCS2:
	case DESC_RATEVHT1SS_MCS3:
		rate_section = 7;
		break;
	case DESC_RATEVHT1SS_MCS4:
	case DESC_RATEVHT1SS_MCS5:
	case DESC_RATEVHT1SS_MCS6:
	case DESC_RATEVHT1SS_MCS7:
		rate_section = 8;
		break;
	case DESC_RATEVHT1SS_MCS8:
	case DESC_RATEVHT1SS_MCS9:
	case DESC_RATEVHT2SS_MCS0:
	case DESC_RATEVHT2SS_MCS1:
		rate_section = 9;
		break;
	case DESC_RATEVHT2SS_MCS2:
	case DESC_RATEVHT2SS_MCS3:
	case DESC_RATEVHT2SS_MCS4:
	case DESC_RATEVHT2SS_MCS5:
		rate_section = 10;
		break;
	case DESC_RATEVHT2SS_MCS6:
	case DESC_RATEVHT2SS_MCS7:
	case DESC_RATEVHT2SS_MCS8:
	case DESC_RATEVHT2SS_MCS9:
		rate_section = 11;
		break;
	default:
		WARN_ONCE(true, "rtl8821ae: Rate_Section is Illegal\n");
		break;
	}

	return rate_section;
}