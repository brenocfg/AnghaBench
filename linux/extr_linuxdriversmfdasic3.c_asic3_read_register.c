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
typedef  int /*<<< orphan*/  u32 ;
struct asic3 {unsigned int bus_shift; scalar_t__ mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  ioread16 (scalar_t__) ; 

u32 asic3_read_register(struct asic3 *asic, unsigned int reg)
{
	return ioread16(asic->mapping +
			(reg >> asic->bus_shift));
}