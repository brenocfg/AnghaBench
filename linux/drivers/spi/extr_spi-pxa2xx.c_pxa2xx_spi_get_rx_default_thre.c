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
#define  CE4100_SSP 129 
#define  QUARK_X1000_SSP 128 
 int /*<<< orphan*/  RX_THRESH_CE4100_DFLT ; 
 int /*<<< orphan*/  RX_THRESH_DFLT ; 
 int /*<<< orphan*/  RX_THRESH_QUARK_X1000_DFLT ; 

__attribute__((used)) static u32
pxa2xx_spi_get_rx_default_thre(const struct driver_data *drv_data)
{
	switch (drv_data->ssp_type) {
	case QUARK_X1000_SSP:
		return RX_THRESH_QUARK_X1000_DFLT;
	case CE4100_SSP:
		return RX_THRESH_CE4100_DFLT;
	default:
		return RX_THRESH_DFLT;
	}
}