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
struct mmc_command {int dummy; } ;

/* Variables and functions */
#define  MMC_RSP_SPI_R1 131 
#define  MMC_RSP_SPI_R1B 130 
#define  MMC_RSP_SPI_R2 129 
#define  MMC_RSP_SPI_R3 128 
 int mmc_spi_resp_type (struct mmc_command*) ; 

__attribute__((used)) static char *maptype(struct mmc_command *cmd)
{
	switch (mmc_spi_resp_type(cmd)) {
	case MMC_RSP_SPI_R1:	return "R1";
	case MMC_RSP_SPI_R1B:	return "R1B";
	case MMC_RSP_SPI_R2:	return "R2/R5";
	case MMC_RSP_SPI_R3:	return "R3/R4/R7";
	default:		return "?";
	}
}