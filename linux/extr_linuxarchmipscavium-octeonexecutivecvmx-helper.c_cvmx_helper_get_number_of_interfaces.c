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
 int /*<<< orphan*/  OCTEON_CN52XX ; 
 int /*<<< orphan*/  OCTEON_CN56XX ; 
 int /*<<< orphan*/  OCTEON_CN68XX ; 
 int /*<<< orphan*/  OCTEON_CN7XXX ; 
 scalar_t__ OCTEON_IS_MODEL (int /*<<< orphan*/ ) ; 

int cvmx_helper_get_number_of_interfaces(void)
{
	if (OCTEON_IS_MODEL(OCTEON_CN68XX))
		return 9;
	if (OCTEON_IS_MODEL(OCTEON_CN56XX) || OCTEON_IS_MODEL(OCTEON_CN52XX))
		return 4;
	if (OCTEON_IS_MODEL(OCTEON_CN7XXX))
		return 5;
	else
		return 3;
}