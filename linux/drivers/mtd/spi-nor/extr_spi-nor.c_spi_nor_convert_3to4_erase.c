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
#define  SPINOR_OP_BE_32K 133 
#define  SPINOR_OP_BE_32K_4B 132 
#define  SPINOR_OP_BE_4K 131 
#define  SPINOR_OP_BE_4K_4B 130 
#define  SPINOR_OP_SE 129 
#define  SPINOR_OP_SE_4B 128 
 TYPE_1__ spi_nor_convert_opcode (TYPE_1__,TYPE_1__ const**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 spi_nor_convert_3to4_erase(u8 opcode)
{
	static const u8 spi_nor_3to4_erase[][2] = {
		{ SPINOR_OP_BE_4K,	SPINOR_OP_BE_4K_4B },
		{ SPINOR_OP_BE_32K,	SPINOR_OP_BE_32K_4B },
		{ SPINOR_OP_SE,		SPINOR_OP_SE_4B },
	};

	return spi_nor_convert_opcode(opcode, spi_nor_3to4_erase,
				      ARRAY_SIZE(spi_nor_3to4_erase));
}