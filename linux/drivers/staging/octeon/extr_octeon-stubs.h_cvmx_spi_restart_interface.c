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
typedef  int /*<<< orphan*/  cvmx_spi_mode_t ;

/* Variables and functions */

__attribute__((used)) static inline int cvmx_spi_restart_interface(int interface,
					cvmx_spi_mode_t mode, int timeout)
{
	return 0;
}