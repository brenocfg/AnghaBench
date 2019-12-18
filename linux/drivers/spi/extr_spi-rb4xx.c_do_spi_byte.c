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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct rb4xx_spi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_spi_clk (struct rb4xx_spi*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void do_spi_byte(struct rb4xx_spi *rbspi, u32 spi_ioc, u8 byte)
{
	int i;

	for (i = 7; i >= 0; i--)
		do_spi_clk(rbspi, spi_ioc, byte >> i);
}