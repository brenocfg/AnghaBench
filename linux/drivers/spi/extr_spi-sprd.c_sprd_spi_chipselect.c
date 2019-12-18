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
typedef  int /*<<< orphan*/  u32 ;
struct sprd_spi {scalar_t__ base; } ;
struct spi_device {struct spi_controller* controller; } ;
struct spi_controller {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPRD_SPI_CS0_VALID ; 
 int /*<<< orphan*/  SPRD_SPI_CSN_MASK ; 
 scalar_t__ SPRD_SPI_CTL0 ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 
 struct sprd_spi* spi_controller_get_devdata (struct spi_controller*) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void sprd_spi_chipselect(struct spi_device *sdev, bool cs)
{
	struct spi_controller *sctlr = sdev->controller;
	struct sprd_spi *ss = spi_controller_get_devdata(sctlr);
	u32 val;

	val = readl_relaxed(ss->base + SPRD_SPI_CTL0);
	/*  The SPI controller will pull down CS pin if cs is 0 */
	if (!cs) {
		val &= ~SPRD_SPI_CS0_VALID;
		writel_relaxed(val, ss->base + SPRD_SPI_CTL0);
	} else {
		val |= SPRD_SPI_CSN_MASK;
		writel_relaxed(val, ss->base + SPRD_SPI_CTL0);
	}
}