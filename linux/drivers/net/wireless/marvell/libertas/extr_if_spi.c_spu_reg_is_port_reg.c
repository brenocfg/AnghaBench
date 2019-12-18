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
typedef  int u16 ;

/* Variables and functions */
#define  IF_SPI_CMD_RDWRPORT_REG 130 
#define  IF_SPI_DATA_RDWRPORT_REG 129 
#define  IF_SPI_IO_RDWRPORT_REG 128 

__attribute__((used)) static inline int spu_reg_is_port_reg(u16 reg)
{
	switch (reg) {
	case IF_SPI_IO_RDWRPORT_REG:
	case IF_SPI_CMD_RDWRPORT_REG:
	case IF_SPI_DATA_RDWRPORT_REG:
		return 1;
	default:
		return 0;
	}
}