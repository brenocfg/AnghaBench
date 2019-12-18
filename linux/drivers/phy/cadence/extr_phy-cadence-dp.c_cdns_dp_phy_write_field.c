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
struct cdns_dp_phy {scalar_t__ base; } ;

/* Variables and functions */
 unsigned int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static void cdns_dp_phy_write_field(struct cdns_dp_phy *cdns_phy,
				    unsigned int offset,
				    unsigned char start_bit,
				    unsigned char num_bits,
				    unsigned int val)
{
	unsigned int read_val;

	read_val = readl(cdns_phy->base + offset);
	writel(((val << start_bit) | (read_val & ~(((1 << num_bits) - 1) <<
		start_bit))), cdns_phy->base + offset);
}