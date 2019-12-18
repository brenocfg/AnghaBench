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
#define  ATOM_SRC_BYTE0 135 
#define  ATOM_SRC_BYTE16 134 
#define  ATOM_SRC_BYTE24 133 
#define  ATOM_SRC_BYTE8 132 
#define  ATOM_SRC_DWORD 131 
#define  ATOM_SRC_WORD0 130 
#define  ATOM_SRC_WORD16 129 
#define  ATOM_SRC_WORD8 128 
 int U16 (int) ; 
 int U32 (int) ; 
 int U8 (int) ; 

__attribute__((used)) static uint32_t atom_get_src_direct(atom_exec_context *ctx, uint8_t align, int *ptr)
{
	uint32_t val = 0xCDCDCDCD;

	switch (align) {
	case ATOM_SRC_DWORD:
		val = U32(*ptr);
		(*ptr) += 4;
		break;
	case ATOM_SRC_WORD0:
	case ATOM_SRC_WORD8:
	case ATOM_SRC_WORD16:
		val = U16(*ptr);
		(*ptr) += 2;
		break;
	case ATOM_SRC_BYTE0:
	case ATOM_SRC_BYTE8:
	case ATOM_SRC_BYTE16:
	case ATOM_SRC_BYTE24:
		val = U8(*ptr);
		(*ptr)++;
		break;
	}
	return val;
}