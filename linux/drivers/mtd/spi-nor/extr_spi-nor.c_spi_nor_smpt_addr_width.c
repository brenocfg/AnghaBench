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
struct spi_nor {int addr_width; } ;

/* Variables and functions */
#define  SMPT_CMD_ADDRESS_LEN_0 131 
#define  SMPT_CMD_ADDRESS_LEN_3 130 
#define  SMPT_CMD_ADDRESS_LEN_4 129 
 int const SMPT_CMD_ADDRESS_LEN_MASK ; 
#define  SMPT_CMD_ADDRESS_LEN_USE_CURRENT 128 

__attribute__((used)) static u8 spi_nor_smpt_addr_width(const struct spi_nor *nor, const u32 settings)
{
	switch (settings & SMPT_CMD_ADDRESS_LEN_MASK) {
	case SMPT_CMD_ADDRESS_LEN_0:
		return 0;
	case SMPT_CMD_ADDRESS_LEN_3:
		return 3;
	case SMPT_CMD_ADDRESS_LEN_4:
		return 4;
	case SMPT_CMD_ADDRESS_LEN_USE_CURRENT:
		/* fall through */
	default:
		return nor->addr_width;
	}
}