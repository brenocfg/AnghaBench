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

int __cvmx_helper_npi_probe(int interface)
{
#if CVMX_PKO_QUEUES_PER_PORT_PCI > 0
	if (OCTEON_IS_MODEL(OCTEON_CN38XX) || OCTEON_IS_MODEL(OCTEON_CN58XX))
		return 4;
	else if (OCTEON_IS_MODEL(OCTEON_CN56XX)
		 && !OCTEON_IS_MODEL(OCTEON_CN56XX_PASS1_X))
		/* The packet engines didn't exist before pass 2 */
		return 4;
	else if (OCTEON_IS_MODEL(OCTEON_CN52XX)
		 && !OCTEON_IS_MODEL(OCTEON_CN52XX_PASS1_X))
		/* The packet engines didn't exist before pass 2 */
		return 4;
#if 0
	/*
	 * Technically CN30XX, CN31XX, and CN50XX contain packet
	 * engines, but nobody ever uses them. Since this is the case,
	 * we disable them here.
	 */
	else if (OCTEON_IS_MODEL(OCTEON_CN31XX)
		 || OCTEON_IS_MODEL(OCTEON_CN50XX))
		return 2;
	else if (OCTEON_IS_MODEL(OCTEON_CN30XX))
		return 1;
#endif
#endif
	return 0;
}