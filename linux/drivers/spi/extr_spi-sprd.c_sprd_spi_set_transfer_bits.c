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
struct sprd_spi {scalar_t__ base; } ;

/* Variables and functions */
 int SPRD_SPI_CHNL_LEN ; 
 int SPRD_SPI_CHNL_LEN_MASK ; 
 scalar_t__ SPRD_SPI_CTL0 ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void sprd_spi_set_transfer_bits(struct sprd_spi *ss, u32 bits)
{
	u32 val = readl_relaxed(ss->base + SPRD_SPI_CTL0);

	/* Set the valid bits for every transaction */
	val &= ~(SPRD_SPI_CHNL_LEN_MASK << SPRD_SPI_CHNL_LEN);
	val |= bits << SPRD_SPI_CHNL_LEN;
	writel_relaxed(val, ss->base + SPRD_SPI_CTL0);
}