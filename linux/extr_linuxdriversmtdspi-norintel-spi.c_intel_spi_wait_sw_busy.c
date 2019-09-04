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
struct intel_spi {scalar_t__ sregs; } ;

/* Variables and functions */
 int INTEL_SPI_TIMEOUT ; 
 scalar_t__ SSFSTS_CTL ; 
 int SSFSTS_CTL_SCIP ; 
 int readl_poll_timeout (scalar_t__,int,int,int,int) ; 

__attribute__((used)) static int intel_spi_wait_sw_busy(struct intel_spi *ispi)
{
	u32 val;

	return readl_poll_timeout(ispi->sregs + SSFSTS_CTL, val,
				  !(val & SSFSTS_CTL_SCIP), 40,
				  INTEL_SPI_TIMEOUT * 1000);
}