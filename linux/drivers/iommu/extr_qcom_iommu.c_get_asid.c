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
typedef  int u32 ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ of_property_read_u32_index (struct device_node const*,char*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int get_asid(const struct device_node *np)
{
	u32 reg;

	/* read the "reg" property directly to get the relative address
	 * of the context bank, and calculate the asid from that:
	 */
	if (of_property_read_u32_index(np, "reg", 0, &reg))
		return -ENODEV;

	return reg / 0x1000;      /* context banks are 0x1000 apart */
}