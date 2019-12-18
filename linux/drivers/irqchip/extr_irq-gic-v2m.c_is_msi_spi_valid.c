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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 scalar_t__ V2M_MAX_SPI ; 
 scalar_t__ V2M_MIN_SPI ; 
 int /*<<< orphan*/  pr_err (char*,scalar_t__,...) ; 

__attribute__((used)) static bool is_msi_spi_valid(u32 base, u32 num)
{
	if (base < V2M_MIN_SPI) {
		pr_err("Invalid MSI base SPI (base:%u)\n", base);
		return false;
	}

	if ((num == 0) || (base + num > V2M_MAX_SPI)) {
		pr_err("Number of SPIs (%u) exceed maximum (%u)\n",
		       num, V2M_MAX_SPI - V2M_MIN_SPI + 1);
		return false;
	}

	return true;
}