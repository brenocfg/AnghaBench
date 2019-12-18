#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ u8 ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (TYPE_1__ const**) ; 
#define  SPINOR_OP_READ 149 
#define  SPINOR_OP_READ_1_1_1_DTR 148 
#define  SPINOR_OP_READ_1_1_1_DTR_4B 147 
#define  SPINOR_OP_READ_1_1_2 146 
#define  SPINOR_OP_READ_1_1_2_4B 145 
#define  SPINOR_OP_READ_1_1_4 144 
#define  SPINOR_OP_READ_1_1_4_4B 143 
#define  SPINOR_OP_READ_1_1_8 142 
#define  SPINOR_OP_READ_1_1_8_4B 141 
#define  SPINOR_OP_READ_1_2_2 140 
#define  SPINOR_OP_READ_1_2_2_4B 139 
#define  SPINOR_OP_READ_1_2_2_DTR 138 
#define  SPINOR_OP_READ_1_2_2_DTR_4B 137 
#define  SPINOR_OP_READ_1_4_4 136 
#define  SPINOR_OP_READ_1_4_4_4B 135 
#define  SPINOR_OP_READ_1_4_4_DTR 134 
#define  SPINOR_OP_READ_1_4_4_DTR_4B 133 
#define  SPINOR_OP_READ_1_8_8 132 
#define  SPINOR_OP_READ_1_8_8_4B 131 
#define  SPINOR_OP_READ_4B 130 
#define  SPINOR_OP_READ_FAST 129 
#define  SPINOR_OP_READ_FAST_4B 128 
 TYPE_1__ spi_nor_convert_opcode (TYPE_1__,TYPE_1__ const**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 spi_nor_convert_3to4_read(u8 opcode)
{
	static const u8 spi_nor_3to4_read[][2] = {
		{ SPINOR_OP_READ,	SPINOR_OP_READ_4B },
		{ SPINOR_OP_READ_FAST,	SPINOR_OP_READ_FAST_4B },
		{ SPINOR_OP_READ_1_1_2,	SPINOR_OP_READ_1_1_2_4B },
		{ SPINOR_OP_READ_1_2_2,	SPINOR_OP_READ_1_2_2_4B },
		{ SPINOR_OP_READ_1_1_4,	SPINOR_OP_READ_1_1_4_4B },
		{ SPINOR_OP_READ_1_4_4,	SPINOR_OP_READ_1_4_4_4B },
		{ SPINOR_OP_READ_1_1_8,	SPINOR_OP_READ_1_1_8_4B },
		{ SPINOR_OP_READ_1_8_8,	SPINOR_OP_READ_1_8_8_4B },

		{ SPINOR_OP_READ_1_1_1_DTR,	SPINOR_OP_READ_1_1_1_DTR_4B },
		{ SPINOR_OP_READ_1_2_2_DTR,	SPINOR_OP_READ_1_2_2_DTR_4B },
		{ SPINOR_OP_READ_1_4_4_DTR,	SPINOR_OP_READ_1_4_4_DTR_4B },
	};

	return spi_nor_convert_opcode(opcode, spi_nor_3to4_read,
				      ARRAY_SIZE(spi_nor_3to4_read));
}