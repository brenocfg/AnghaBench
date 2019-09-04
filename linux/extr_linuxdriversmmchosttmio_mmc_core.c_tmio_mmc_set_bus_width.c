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
typedef  int u16 ;
struct tmio_mmc_host {int dummy; } ;

/* Variables and functions */
 int CARD_OPT_WIDTH ; 
 int CARD_OPT_WIDTH8 ; 
 int /*<<< orphan*/  CTL_SD_MEM_CARD_OPT ; 
 unsigned char MMC_BUS_WIDTH_1 ; 
 unsigned char MMC_BUS_WIDTH_8 ; 
 int sd_ctrl_read16 (struct tmio_mmc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_ctrl_write16 (struct tmio_mmc_host*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void tmio_mmc_set_bus_width(struct tmio_mmc_host *host,
				   unsigned char bus_width)
{
	u16 reg = sd_ctrl_read16(host, CTL_SD_MEM_CARD_OPT)
				& ~(CARD_OPT_WIDTH | CARD_OPT_WIDTH8);

	/* reg now applies to MMC_BUS_WIDTH_4 */
	if (bus_width == MMC_BUS_WIDTH_1)
		reg |= CARD_OPT_WIDTH;
	else if (bus_width == MMC_BUS_WIDTH_8)
		reg |= CARD_OPT_WIDTH8;

	sd_ctrl_write16(host, CTL_SD_MEM_CARD_OPT, reg);
}