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
struct gpmi_nand_data {int dummy; } ;

/* Variables and functions */
 scalar_t__ GPMI_IS_MX23 (struct gpmi_nand_data*) ; 
 int mx23_boot_init (struct gpmi_nand_data*) ; 
 int /*<<< orphan*/  nand_boot_set_geometry (struct gpmi_nand_data*) ; 

__attribute__((used)) static int nand_boot_init(struct gpmi_nand_data  *this)
{
	nand_boot_set_geometry(this);

	/* This is ROM arch-specific initilization before the BBT scanning. */
	if (GPMI_IS_MX23(this))
		return mx23_boot_init(this);
	return 0;
}