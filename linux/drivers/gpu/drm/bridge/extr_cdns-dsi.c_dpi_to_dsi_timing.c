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

/* Variables and functions */
 unsigned int DIV_ROUND_UP (unsigned int,int) ; 

__attribute__((used)) static unsigned int dpi_to_dsi_timing(unsigned int dpi_timing,
				      unsigned int dpi_bpp,
				      unsigned int dsi_pkt_overhead)
{
	unsigned int dsi_timing = DIV_ROUND_UP(dpi_timing * dpi_bpp, 8);

	if (dsi_timing < dsi_pkt_overhead)
		dsi_timing = 0;
	else
		dsi_timing -= dsi_pkt_overhead;

	return dsi_timing;
}