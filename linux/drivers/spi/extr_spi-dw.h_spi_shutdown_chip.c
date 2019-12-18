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
struct dw_spi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  spi_enable_chip (struct dw_spi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_set_clk (struct dw_spi*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void spi_shutdown_chip(struct dw_spi *dws)
{
	spi_enable_chip(dws, 0);
	spi_set_clk(dws, 0);
}