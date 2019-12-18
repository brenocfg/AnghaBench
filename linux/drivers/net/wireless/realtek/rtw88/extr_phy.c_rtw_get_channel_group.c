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

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 

__attribute__((used)) static u8 rtw_get_channel_group(u8 channel)
{
	switch (channel) {
	default:
		WARN_ON(1);
		/* fall through */
	case 1:
	case 2:
	case 36:
	case 38:
	case 40:
	case 42:
		return 0;
	case 3:
	case 4:
	case 5:
	case 44:
	case 46:
	case 48:
	case 50:
		return 1;
	case 6:
	case 7:
	case 8:
	case 52:
	case 54:
	case 56:
	case 58:
		return 2;
	case 9:
	case 10:
	case 11:
	case 60:
	case 62:
	case 64:
		return 3;
	case 12:
	case 13:
	case 100:
	case 102:
	case 104:
	case 106:
		return 4;
	case 14:
	case 108:
	case 110:
	case 112:
	case 114:
		return 5;
	case 116:
	case 118:
	case 120:
	case 122:
		return 6;
	case 124:
	case 126:
	case 128:
	case 130:
		return 7;
	case 132:
	case 134:
	case 136:
	case 138:
		return 8;
	case 140:
	case 142:
	case 144:
		return 9;
	case 149:
	case 151:
	case 153:
	case 155:
		return 10;
	case 157:
	case 159:
	case 161:
		return 11;
	case 165:
	case 167:
	case 169:
	case 171:
		return 12;
	case 173:
	case 175:
	case 177:
		return 13;
	}
}