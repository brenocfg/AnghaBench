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
typedef  scalar_t__ u8 ;
struct driver_data {scalar_t__ n_bytes; scalar_t__ rx; scalar_t__ rx_end; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSDR ; 
 int /*<<< orphan*/  SSSR ; 
 int SSSR_RNE ; 
 int pxa2xx_spi_read (struct driver_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int null_reader(struct driver_data *drv_data)
{
	u8 n_bytes = drv_data->n_bytes;

	while ((pxa2xx_spi_read(drv_data, SSSR) & SSSR_RNE)
	       && (drv_data->rx < drv_data->rx_end)) {
		pxa2xx_spi_read(drv_data, SSDR);
		drv_data->rx += n_bytes;
	}

	return drv_data->rx == drv_data->rx_end;
}