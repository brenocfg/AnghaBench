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
typedef  int /*<<< orphan*/  cvmx_helper_link_info_t ;

/* Variables and functions */

int __cvmx_helper_spi_link_set(int ipd_port, cvmx_helper_link_info_t link_info)
{
	/* Nothing to do. If we have a SPI4000 then the setup was already performed
	   by cvmx_spi4000_check_speed(). If not then there isn't any link
	   info */
	return 0;
}