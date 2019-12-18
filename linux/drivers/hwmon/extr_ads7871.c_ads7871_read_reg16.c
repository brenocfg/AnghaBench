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
struct spi_device {int dummy; } ;

/* Variables and functions */
 int INST_16BIT_BM ; 
 int INST_READ_BM ; 
 int spi_w8r16 (struct spi_device*,int) ; 

__attribute__((used)) static int ads7871_read_reg16(struct spi_device *spi, int reg)
{
	int ret;
	reg = reg | INST_READ_BM | INST_16BIT_BM;
	ret = spi_w8r16(spi, reg);
	return ret;
}