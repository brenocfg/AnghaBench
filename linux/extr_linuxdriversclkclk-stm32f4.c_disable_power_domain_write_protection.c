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
 scalar_t__ pdrm ; 
 int /*<<< orphan*/  regmap_update_bits (scalar_t__,int,int,int) ; 

__attribute__((used)) static inline void disable_power_domain_write_protection(void)
{
	if (pdrm)
		regmap_update_bits(pdrm, 0x00, (1 << 8), (1 << 8));
}