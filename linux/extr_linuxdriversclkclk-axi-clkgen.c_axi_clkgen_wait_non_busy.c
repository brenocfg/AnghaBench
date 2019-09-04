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
struct axi_clkgen {int dummy; } ;

/* Variables and functions */
 unsigned int AXI_CLKGEN_V2_DRP_STATUS_BUSY ; 
 int /*<<< orphan*/  AXI_CLKGEN_V2_REG_DRP_STATUS ; 
 int EIO ; 
 int /*<<< orphan*/  axi_clkgen_read (struct axi_clkgen*,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int axi_clkgen_wait_non_busy(struct axi_clkgen *axi_clkgen)
{
	unsigned int timeout = 10000;
	unsigned int val;

	do {
		axi_clkgen_read(axi_clkgen, AXI_CLKGEN_V2_REG_DRP_STATUS, &val);
	} while ((val & AXI_CLKGEN_V2_DRP_STATUS_BUSY) && --timeout);

	if (val & AXI_CLKGEN_V2_DRP_STATUS_BUSY)
		return -EIO;

	return val & 0xffff;
}