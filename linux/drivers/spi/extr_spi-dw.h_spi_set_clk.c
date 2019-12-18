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
typedef  int /*<<< orphan*/  u16 ;
struct dw_spi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DW_SPI_BAUDR ; 
 int /*<<< orphan*/  dw_writel (struct dw_spi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void spi_set_clk(struct dw_spi *dws, u16 div)
{
	dw_writel(dws, DW_SPI_BAUDR, div);
}