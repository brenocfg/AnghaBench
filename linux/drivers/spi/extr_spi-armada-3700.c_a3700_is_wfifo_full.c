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
struct a3700_spi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  A3700_SPI_IF_CTRL_REG ; 
 int A3700_SPI_WFIFO_FULL ; 
 int spireg_read (struct a3700_spi*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int a3700_is_wfifo_full(struct a3700_spi *a3700_spi)
{
	u32 val;

	val = spireg_read(a3700_spi, A3700_SPI_IF_CTRL_REG);
	return (val & A3700_SPI_WFIFO_FULL);
}