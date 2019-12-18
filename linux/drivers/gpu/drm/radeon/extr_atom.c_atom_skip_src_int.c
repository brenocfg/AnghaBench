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
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  atom_exec_context ;

/* Variables and functions */
#define  ATOM_ARG_FB 143 
#define  ATOM_ARG_ID 142 
#define  ATOM_ARG_IMM 141 
#define  ATOM_ARG_MC 140 
#define  ATOM_ARG_PLL 139 
#define  ATOM_ARG_PS 138 
#define  ATOM_ARG_REG 137 
#define  ATOM_ARG_WS 136 
#define  ATOM_SRC_BYTE0 135 
#define  ATOM_SRC_BYTE16 134 
#define  ATOM_SRC_BYTE24 133 
#define  ATOM_SRC_BYTE8 132 
#define  ATOM_SRC_DWORD 131 
#define  ATOM_SRC_WORD0 130 
#define  ATOM_SRC_WORD16 129 
#define  ATOM_SRC_WORD8 128 

__attribute__((used)) static void atom_skip_src_int(atom_exec_context *ctx, uint8_t attr, int *ptr)
{
	uint32_t align = (attr >> 3) & 7, arg = attr & 7;
	switch (arg) {
	case ATOM_ARG_REG:
	case ATOM_ARG_ID:
		(*ptr) += 2;
		break;
	case ATOM_ARG_PLL:
	case ATOM_ARG_MC:
	case ATOM_ARG_PS:
	case ATOM_ARG_WS:
	case ATOM_ARG_FB:
		(*ptr)++;
		break;
	case ATOM_ARG_IMM:
		switch (align) {
		case ATOM_SRC_DWORD:
			(*ptr) += 4;
			return;
		case ATOM_SRC_WORD0:
		case ATOM_SRC_WORD8:
		case ATOM_SRC_WORD16:
			(*ptr) += 2;
			return;
		case ATOM_SRC_BYTE0:
		case ATOM_SRC_BYTE8:
		case ATOM_SRC_BYTE16:
		case ATOM_SRC_BYTE24:
			(*ptr)++;
			return;
		}
		return;
	}
}