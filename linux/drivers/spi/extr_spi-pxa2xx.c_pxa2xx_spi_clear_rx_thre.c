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
struct driver_data {int ssp_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  CE4100_SSCR1_RFT ; 
#define  CE4100_SSP 129 
 int /*<<< orphan*/  QUARK_X1000_SSCR1_RFT ; 
#define  QUARK_X1000_SSP 128 
 int /*<<< orphan*/  SSCR1_RFT ; 

__attribute__((used)) static void pxa2xx_spi_clear_rx_thre(const struct driver_data *drv_data,
				     u32 *sccr1_reg)
{
	u32 mask;

	switch (drv_data->ssp_type) {
	case QUARK_X1000_SSP:
		mask = QUARK_X1000_SSCR1_RFT;
		break;
	case CE4100_SSP:
		mask = CE4100_SSCR1_RFT;
		break;
	default:
		mask = SSCR1_RFT;
		break;
	}
	*sccr1_reg &= ~mask;
}