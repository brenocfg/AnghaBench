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

/* Variables and functions */
#define  OP_31 140 
#define  OP_31_XOP_STBUX 139 
#define  OP_31_XOP_STDUX 138 
#define  OP_31_XOP_STFDUX 137 
#define  OP_31_XOP_STFSUX 136 
#define  OP_31_XOP_STHUX 135 
#define  OP_31_XOP_STWUX 134 
#define  OP_STBU 133 
#define  OP_STD 132 
#define  OP_STFDU 131 
#define  OP_STFSU 130 
#define  OP_STHU 129 
#define  OP_STWU 128 

__attribute__((used)) static bool store_updates_sp(unsigned int inst)
{
	/* check for 1 in the rA field */
	if (((inst >> 16) & 0x1f) != 1)
		return false;
	/* check major opcode */
	switch (inst >> 26) {
	case OP_STWU:
	case OP_STBU:
	case OP_STHU:
	case OP_STFSU:
	case OP_STFDU:
		return true;
	case OP_STD:	/* std or stdu */
		return (inst & 3) == 1;
	case OP_31:
		/* check minor opcode */
		switch ((inst >> 1) & 0x3ff) {
		case OP_31_XOP_STDUX:
		case OP_31_XOP_STWUX:
		case OP_31_XOP_STBUX:
		case OP_31_XOP_STHUX:
		case OP_31_XOP_STFSUX:
		case OP_31_XOP_STFDUX:
			return true;
		}
	}
	return false;
}