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
struct driver_data {int ssp_type; } ;

/* Variables and functions */
#define  CE4100_SSP 129 
 int CE4100_SSSR_TFL_MASK ; 
#define  QUARK_X1000_SSP 128 
 int QUARK_X1000_SSSR_TFL_MASK ; 
 int /*<<< orphan*/  SSSR ; 
 int SSSR_TFL_MASK ; 
 int pxa2xx_spi_read (struct driver_data const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool pxa2xx_spi_txfifo_full(const struct driver_data *drv_data)
{
	u32 mask;

	switch (drv_data->ssp_type) {
	case QUARK_X1000_SSP:
		mask = QUARK_X1000_SSSR_TFL_MASK;
		break;
	case CE4100_SSP:
		mask = CE4100_SSSR_TFL_MASK;
		break;
	default:
		mask = SSSR_TFL_MASK;
		break;
	}

	return (pxa2xx_spi_read(drv_data, SSSR) & mask) == mask;
}