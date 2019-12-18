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
typedef  int /*<<< orphan*/  u8 ;
typedef  unsigned int u32 ;
struct spi_nor {struct cqspi_flash_pdata* priv; } ;
struct cqspi_flash_pdata {unsigned int inst_width; unsigned int addr_width; unsigned int data_width; } ;

/* Variables and functions */
 unsigned int CQSPI_REG_RD_INSTR_TYPE_ADDR_LSB ; 
 unsigned int CQSPI_REG_RD_INSTR_TYPE_DATA_LSB ; 
 unsigned int CQSPI_REG_RD_INSTR_TYPE_INSTR_LSB ; 

__attribute__((used)) static unsigned int cqspi_calc_rdreg(struct spi_nor *nor, const u8 opcode)
{
	struct cqspi_flash_pdata *f_pdata = nor->priv;
	u32 rdreg = 0;

	rdreg |= f_pdata->inst_width << CQSPI_REG_RD_INSTR_TYPE_INSTR_LSB;
	rdreg |= f_pdata->addr_width << CQSPI_REG_RD_INSTR_TYPE_ADDR_LSB;
	rdreg |= f_pdata->data_width << CQSPI_REG_RD_INSTR_TYPE_DATA_LSB;

	return rdreg;
}