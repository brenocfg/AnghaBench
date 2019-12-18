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
struct stm32_spi {int base; } ;

/* Variables and functions */
 int readl_relaxed (int) ; 
 int /*<<< orphan*/  writel_relaxed (int,int) ; 

__attribute__((used)) static inline void stm32_spi_set_bits(struct stm32_spi *spi,
				      u32 offset, u32 bits)
{
	writel_relaxed(readl_relaxed(spi->base + offset) | bits,
		       spi->base + offset);
}