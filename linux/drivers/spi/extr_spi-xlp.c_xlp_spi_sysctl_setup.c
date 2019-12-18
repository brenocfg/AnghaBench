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
struct xlp_spi_priv {int dummy; } ;

/* Variables and functions */
 int XLP_SPI_MAX_CS ; 
 int /*<<< orphan*/  XLP_SPI_SYSCTRL ; 
 int XLP_SPI_SYS_PMEN ; 
 int XLP_SPI_SYS_RESET ; 
 int /*<<< orphan*/  xlp_spi_sysctl_write (struct xlp_spi_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void xlp_spi_sysctl_setup(struct xlp_spi_priv *xspi)
{
	int cs;

	for (cs = 0; cs < XLP_SPI_MAX_CS; cs++)
		xlp_spi_sysctl_write(xspi, XLP_SPI_SYSCTRL,
				XLP_SPI_SYS_RESET << cs);
	xlp_spi_sysctl_write(xspi, XLP_SPI_SYSCTRL, XLP_SPI_SYS_PMEN);
}