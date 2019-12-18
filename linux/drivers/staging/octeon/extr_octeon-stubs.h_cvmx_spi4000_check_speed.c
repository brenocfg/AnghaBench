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
union cvmx_gmxx_rxx_rx_inbnd {scalar_t__ u64; } ;

/* Variables and functions */

__attribute__((used)) static inline union cvmx_gmxx_rxx_rx_inbnd cvmx_spi4000_check_speed(
	int interface,
	int port)
{
	union cvmx_gmxx_rxx_rx_inbnd r;
	r.u64 = 0;
	return r;
}