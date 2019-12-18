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
 scalar_t__ SPRD_SPI_CTL10 ; 
 scalar_t__ SPRD_SPI_CTL11 ; 
 int SPRD_SPI_RX_LEN_H_MASK ; 
 int SPRD_SPI_RX_LEN_H_OFFSET ; 
 int SPRD_SPI_RX_LEN_L_MASK ; 
 int SPRD_SPI_RX_MAX_LEN_MASK ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void sprd_spi_set_rx_length(struct sprd_spi *ss, u32 length)
{
	u32 val = readl_relaxed(ss->base + SPRD_SPI_CTL10);

	length &= SPRD_SPI_RX_MAX_LEN_MASK;
	val &= ~SPRD_SPI_RX_LEN_H_MASK;
	val |= length >> SPRD_SPI_RX_LEN_H_OFFSET;
	writel_relaxed(val, ss->base + SPRD_SPI_CTL10);

	val = length & SPRD_SPI_RX_LEN_L_MASK;
	writel_relaxed(val, ss->base + SPRD_SPI_CTL11);
}