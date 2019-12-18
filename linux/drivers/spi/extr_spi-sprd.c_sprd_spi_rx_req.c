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
struct sprd_spi {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ SPRD_SPI_CTL12 ; 
 int /*<<< orphan*/  SPRD_SPI_SW_RX_REQ ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void sprd_spi_rx_req(struct sprd_spi *ss)
{
	writel_relaxed(SPRD_SPI_SW_RX_REQ, ss->base + SPRD_SPI_CTL12);
}