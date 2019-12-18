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
typedef  int u32 ;
struct spi_master {int dummy; } ;

/* Variables and functions */
 int pch_spi_readreg (struct spi_master*,int) ; 
 int /*<<< orphan*/  pch_spi_writereg (struct spi_master*,int,int) ; 

__attribute__((used)) static inline void pch_spi_setclr_reg(struct spi_master *master, int idx,
				      u32 set, u32 clr)
{
	u32 tmp = pch_spi_readreg(master, idx);
	tmp = (tmp & ~clr) | set;
	pch_spi_writereg(master, idx, tmp);
}