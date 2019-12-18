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
typedef  int s16 ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_871X (char*,int const) ; 
#define  MGN_11M 211 
#define  MGN_12M 210 
#define  MGN_18M 209 
#define  MGN_1M 208 
#define  MGN_24M 207 
#define  MGN_2M 206 
#define  MGN_36M 205 
#define  MGN_48M 204 
#define  MGN_54M 203 
#define  MGN_5_5M 202 
#define  MGN_6M 201 
#define  MGN_9M 200 
#define  MGN_MCS0 199 
#define  MGN_MCS1 198 
#define  MGN_MCS10 197 
#define  MGN_MCS11 196 
#define  MGN_MCS12 195 
#define  MGN_MCS13 194 
#define  MGN_MCS14 193 
#define  MGN_MCS15 192 
#define  MGN_MCS16 191 
#define  MGN_MCS17 190 
#define  MGN_MCS18 189 
#define  MGN_MCS19 188 
#define  MGN_MCS2 187 
#define  MGN_MCS20 186 
#define  MGN_MCS21 185 
#define  MGN_MCS22 184 
#define  MGN_MCS23 183 
#define  MGN_MCS24 182 
#define  MGN_MCS25 181 
#define  MGN_MCS26 180 
#define  MGN_MCS27 179 
#define  MGN_MCS28 178 
#define  MGN_MCS29 177 
#define  MGN_MCS3 176 
#define  MGN_MCS30 175 
#define  MGN_MCS31 174 
#define  MGN_MCS4 173 
#define  MGN_MCS5 172 
#define  MGN_MCS6 171 
#define  MGN_MCS7 170 
#define  MGN_MCS8 169 
#define  MGN_MCS9 168 
#define  MGN_VHT1SS_MCS0 167 
#define  MGN_VHT1SS_MCS1 166 
#define  MGN_VHT1SS_MCS2 165 
#define  MGN_VHT1SS_MCS3 164 
#define  MGN_VHT1SS_MCS4 163 
#define  MGN_VHT1SS_MCS5 162 
#define  MGN_VHT1SS_MCS6 161 
#define  MGN_VHT1SS_MCS7 160 
#define  MGN_VHT1SS_MCS8 159 
#define  MGN_VHT1SS_MCS9 158 
#define  MGN_VHT2SS_MCS0 157 
#define  MGN_VHT2SS_MCS1 156 
#define  MGN_VHT2SS_MCS2 155 
#define  MGN_VHT2SS_MCS3 154 
#define  MGN_VHT2SS_MCS4 153 
#define  MGN_VHT2SS_MCS5 152 
#define  MGN_VHT2SS_MCS6 151 
#define  MGN_VHT2SS_MCS7 150 
#define  MGN_VHT2SS_MCS8 149 
#define  MGN_VHT2SS_MCS9 148 
#define  MGN_VHT3SS_MCS0 147 
#define  MGN_VHT3SS_MCS1 146 
#define  MGN_VHT3SS_MCS2 145 
#define  MGN_VHT3SS_MCS3 144 
#define  MGN_VHT3SS_MCS4 143 
#define  MGN_VHT3SS_MCS5 142 
#define  MGN_VHT3SS_MCS6 141 
#define  MGN_VHT3SS_MCS7 140 
#define  MGN_VHT3SS_MCS8 139 
#define  MGN_VHT3SS_MCS9 138 
#define  MGN_VHT4SS_MCS0 137 
#define  MGN_VHT4SS_MCS1 136 
#define  MGN_VHT4SS_MCS2 135 
#define  MGN_VHT4SS_MCS3 134 
#define  MGN_VHT4SS_MCS4 133 
#define  MGN_VHT4SS_MCS5 132 
#define  MGN_VHT4SS_MCS6 131 
#define  MGN_VHT4SS_MCS7 130 
#define  MGN_VHT4SS_MCS8 129 
#define  MGN_VHT4SS_MCS9 128 

__attribute__((used)) static s16 get_rate_sctn_idx(const u8 rate)
{
	switch (rate) {
	case MGN_1M: case MGN_2M: case MGN_5_5M: case MGN_11M:
		return 0;
	case MGN_6M: case MGN_9M: case MGN_12M: case MGN_18M:
	case MGN_24M: case MGN_36M: case MGN_48M: case MGN_54M:
		return 1;
	case MGN_MCS0: case MGN_MCS1: case MGN_MCS2: case MGN_MCS3:
	case MGN_MCS4: case MGN_MCS5: case MGN_MCS6: case MGN_MCS7:
		return 2;
	case MGN_MCS8: case MGN_MCS9: case MGN_MCS10: case MGN_MCS11:
	case MGN_MCS12: case MGN_MCS13: case MGN_MCS14: case MGN_MCS15:
		return 3;
	case MGN_MCS16: case MGN_MCS17: case MGN_MCS18: case MGN_MCS19:
	case MGN_MCS20: case MGN_MCS21: case MGN_MCS22: case MGN_MCS23:
		return 4;
	case MGN_MCS24: case MGN_MCS25: case MGN_MCS26: case MGN_MCS27:
	case MGN_MCS28: case MGN_MCS29: case MGN_MCS30: case MGN_MCS31:
		return 5;
	case MGN_VHT1SS_MCS0: case MGN_VHT1SS_MCS1: case MGN_VHT1SS_MCS2:
	case MGN_VHT1SS_MCS3: case MGN_VHT1SS_MCS4: case MGN_VHT1SS_MCS5:
	case MGN_VHT1SS_MCS6: case MGN_VHT1SS_MCS7: case MGN_VHT1SS_MCS8:
	case MGN_VHT1SS_MCS9:
		return 6;
	case MGN_VHT2SS_MCS0: case MGN_VHT2SS_MCS1: case MGN_VHT2SS_MCS2:
	case MGN_VHT2SS_MCS3: case MGN_VHT2SS_MCS4: case MGN_VHT2SS_MCS5:
	case MGN_VHT2SS_MCS6: case MGN_VHT2SS_MCS7: case MGN_VHT2SS_MCS8:
	case MGN_VHT2SS_MCS9:
		return 7;
	case MGN_VHT3SS_MCS0: case MGN_VHT3SS_MCS1: case MGN_VHT3SS_MCS2:
	case MGN_VHT3SS_MCS3: case MGN_VHT3SS_MCS4: case MGN_VHT3SS_MCS5:
	case MGN_VHT3SS_MCS6: case MGN_VHT3SS_MCS7: case MGN_VHT3SS_MCS8:
	case MGN_VHT3SS_MCS9:
		return 8;
	case MGN_VHT4SS_MCS0: case MGN_VHT4SS_MCS1: case MGN_VHT4SS_MCS2:
	case MGN_VHT4SS_MCS3: case MGN_VHT4SS_MCS4: case MGN_VHT4SS_MCS5:
	case MGN_VHT4SS_MCS6: case MGN_VHT4SS_MCS7: case MGN_VHT4SS_MCS8:
	case MGN_VHT4SS_MCS9:
		return 9;
	default:
		DBG_871X("Wrong rate 0x%x\n", rate);
		return -1;
	}
}