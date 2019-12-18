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

/* Variables and functions */
 int /*<<< orphan*/  DBG_871X (char*,char*,int*,int*) ; 
 scalar_t__ IsHexDigit (char) ; 
 scalar_t__ MapCharToHexDigit (char) ; 

bool GetHexValueFromString(char *szStr, u32 *pu4bVal, u32 *pu4bMove)
{
	char *szScan = szStr;

	/*  Check input parameter. */
	if (!szStr || !pu4bVal || !pu4bMove) {
		DBG_871X("GetHexValueFromString(): Invalid input arguments! szStr: %p, pu4bVal: %p, pu4bMove: %p\n",
			 szStr, pu4bVal, pu4bMove);
		return false;
	}

	/*  Initialize output. */
	*pu4bMove = 0;
	*pu4bVal = 0;

	/*  Skip leading space. */
	while (*szScan != '\0' && (*szScan == ' ' || *szScan == '\t')) {
		szScan++;
		(*pu4bMove)++;
	}

	/*  Skip leading '0x' or '0X'. */
	if (*szScan == '0' && (*(szScan+1) == 'x' || *(szScan+1) == 'X')) {
		szScan += 2;
		(*pu4bMove) += 2;
	}

	/*  Check if szScan is now pointer to a character for hex digit, */
	/*  if not, it means this is not a valid hex number. */
	if (!IsHexDigit(*szScan))
		return false;

	/*  Parse each digit. */
	do {
		(*pu4bVal) <<= 4;
		*pu4bVal += MapCharToHexDigit(*szScan);

		szScan++;
		(*pu4bMove)++;
	} while (IsHexDigit(*szScan));

	return true;
}