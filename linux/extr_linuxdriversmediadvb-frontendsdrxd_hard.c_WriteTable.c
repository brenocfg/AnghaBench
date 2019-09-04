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
typedef  int u32 ;
typedef  int u16 ;
struct drxd_state {int dummy; } ;

/* Variables and functions */
 int WriteBlock (struct drxd_state*,int,int,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int WriteTable(struct drxd_state *state, u8 * pTable)
{
	int status = 0;

	if (!pTable)
		return 0;

	while (!status) {
		u16 Length;
		u32 Address = pTable[0] | (pTable[1] << 8) |
		    (pTable[2] << 16) | (pTable[3] << 24);

		if (Address == 0xFFFFFFFF)
			break;
		pTable += sizeof(u32);

		Length = pTable[0] | (pTable[1] << 8);
		pTable += sizeof(u16);
		if (!Length)
			break;
		status = WriteBlock(state, Address, Length * 2, pTable, 0);
		pTable += (Length * 2);
	}
	return status;
}